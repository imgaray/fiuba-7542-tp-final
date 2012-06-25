#include "TabAdminConfigConsultas.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "TabConfigVista.h"

// botones
#define BUTTON_AGREGAR_TAB "buttonAgregarTab"
#define BUTTON_GUARDAR_CAMBIOS_TAB "buttonGuardarCambiosTab"
#define BUTTON_ELIMINAR_TAB "buttonEliminarTab"

// config tabs
#define HBOX_TAB_SELEC "hboxTabSelec"
#define TABLE_TAB_SELEC "tableTabSelec"

#include <iostream>
TabAdminConfigConsultas::TabAdminConfigConsultas(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder), guardandoCambios(false) {
    initBotones();
    initTabConfig();
}

TabAdminConfigConsultas::~TabAdminConfigConsultas() {
    // lo agrego por ser más simple y óptimo iterar sobre una lista que un mapa
    pTabModeloActual = mapaConsultasConfiguradas[NOMBRE_TAB_POR_DEFECTO];
    consultasConfiguradas.push_back(pTabModeloActual);

    std::list< TabConfigModelo* >::iterator it = consultasConfiguradas.begin();
    for ( ; it != consultasConfiguradas.end(); ++it) {
        pTabModeloActual = *it; // para evitar un warning del compilador
        delete pTabModeloActual;
    }
}

void TabAdminConfigConsultas::initBotones() {
    Gtk::Button* pAux;
    builder->get_widget(BUTTON_AGREGAR_TAB, pAux);
    if (pAux) {
        botones[BUTTON_AGREGAR_TAB] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &TabAdminConfigConsultas::on_agregar_tab_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_AGREGAR_TAB);

    builder->get_widget(BUTTON_GUARDAR_CAMBIOS_TAB, pAux);
    if (pAux) {
        botones[BUTTON_GUARDAR_CAMBIOS_TAB] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &TabAdminConfigConsultas::on_guardar_cambios_tab_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_GUARDAR_CAMBIOS_TAB);

    builder->get_widget(BUTTON_ELIMINAR_TAB, pAux);
    if (pAux) {
        botones[BUTTON_ELIMINAR_TAB] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &TabAdminConfigConsultas::on_eliminar_tab_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_ELIMINAR_TAB);
}

void TabAdminConfigConsultas::initTabConfig() {
    builder->get_widget_derived(TABLE_TAB_SELEC, pTabVista);
    if (!pTabVista)
        throw ExcepcionArchivoGladeCorrupto(TABLE_TAB_SELEC);

    Gtk::HBox* pHBoxTabSelec;
    builder->get_widget(HBOX_TAB_SELEC, pHBoxTabSelec);
    if (pHBoxTabSelec) {
        pHBoxTabSelec->pack_start(comboTabSelec, false, false);
        comboTabSelec.show();
    } else
        throw ExcepcionArchivoGladeCorrupto(HBOX_TAB_SELEC);

    comboTabSelec.signal_changed().connect(sigc::mem_fun(*this,
        &TabAdminConfigConsultas::on_combo_tab_selec_changed));

    pTabModeloActual = new TabConfigModelo();
    mapaConsultasConfiguradas[NOMBRE_TAB_POR_DEFECTO] = pTabModeloActual;

    comboTabSelec.append_text(NOMBRE_TAB_POR_DEFECTO);
    comboTabSelec.set_active(0);
}

void TabAdminConfigConsultas::on_agregar_tab_button_clicked() {
    std::cout << BUTTON_AGREGAR_TAB " clicked." << std::endl;
    // pedirle a TabConfigVista el título de la tab, verificar que no exista para ver si se puede agregar
    // lo que hace TabConfigVista es retornar un modelo nuevo por defecto
    // como la entrada mapaConsultasConfiguradas[NOMBRE_TAB_POR_DEFECTO] ya existe, se pisa ese valor con el nuevo
    // y se agrega la entrada según el nombre en el mapa, en la lista el puntero, y en el combobox ese nombre y se
    // pone como activo
    Glib::ustring tabLabel = pTabModeloActual->getTabLabelNueva();
    if (mapaConsultasConfiguradas.find(tabLabel) == mapaConsultasConfiguradas.end()) {
        pTabModeloActual->setTabLabelNuevaComoValida();
        mapaConsultasConfiguradas[tabLabel] = pTabModeloActual;
        consultasConfiguradas.push_back(pTabModeloActual);
        comboTabSelec.append_text(tabLabel);
        comboTabSelec.set_active_text(tabLabel);
        mapaConsultasConfiguradas[NOMBRE_TAB_POR_DEFECTO] = new TabConfigModelo();
    }
}

void TabAdminConfigConsultas::on_guardar_cambios_tab_button_clicked() {
    std::cout << BUTTON_GUARDAR_CAMBIOS_TAB " clicked." << std::endl;

    Glib::ustring tabLabelNueva = pTabModeloActual->getTabLabelNueva();
    // si lo encuentra en el mapa, es porque no es válido
    if (mapaConsultasConfiguradas.find(tabLabelNueva) != mapaConsultasConfiguradas.end())
        return;
    if (tabLabelNueva == NOMBRE_TAB_POR_DEFECTO)
        return;

    guardandoCambios = true;
        int pos = comboTabSelec.get_active_row_number();
        Glib::ustring labelVieja = pTabModeloActual->getTabLabel();
        comboTabSelec.remove_text(labelVieja);
        mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(labelVieja));
        mapaConsultasConfiguradas[tabLabelNueva] = pTabModeloActual;
        comboTabSelec.insert_text(pos, tabLabelNueva);
    guardandoCambios = false;
    comboTabSelec.set_active(pos);
}

void TabAdminConfigConsultas::on_eliminar_tab_button_clicked() {
    std::cout << BUTTON_ELIMINAR_TAB " clicked." << std::endl;
    // eliminar modelo seleccionado, remover del mapa, la lista y del combobox
    // busco por el label viejo porque es con el que está en el mapa hasta que se aplican los cambios

    Glib::ustring label = pTabModeloActual->getTabLabel();
    mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(label));

    std::list< TabConfigModelo* >::iterator it = consultasConfiguradas.begin();
    bool encontrado = false;
    while (!encontrado && it != consultasConfiguradas.end())
        encontrado = (*(it++)) == pTabModeloActual;

    if (encontrado)
        consultasConfiguradas.erase(--it);
    delete pTabModeloActual;

    guardandoCambios = true;
        int pos = comboTabSelec.get_active_row_number();
        comboTabSelec.remove_text(label);
    guardandoCambios = false;
    comboTabSelec.set_active(pos-1);
}

void TabAdminConfigConsultas::on_combo_tab_selec_changed() {
    if (guardandoCambios)
        return;
    Glib::ustring tabLabel = comboTabSelec.get_active_text();
    if (tabLabel == NOMBRE_TAB_POR_DEFECTO) {
        botones[BUTTON_AGREGAR_TAB]->show();
        botones[BUTTON_GUARDAR_CAMBIOS_TAB]->hide();
        botones[BUTTON_ELIMINAR_TAB]->hide();
    } else {
        botones[BUTTON_AGREGAR_TAB]->hide();
        botones[BUTTON_GUARDAR_CAMBIOS_TAB]->show();
        botones[BUTTON_ELIMINAR_TAB]->show();
    }

    pTabModeloActual = mapaConsultasConfiguradas[tabLabel];
    pTabVista->setModelo(pTabModeloActual);
}

bool TabAdminConfigConsultas::aplicarCambios() {
    std::cout << "bool TabAdminConfigConsultas::aplicarCambios()... guardando en archivo (@todo)" << std::endl;
    return true;
}
