#include "AdminConfigObjManager.h"
#include "TabConfigModelo.h"
#include "PanelConfigModelo.h"

AdminConfigObjManager::AdminConfigObjManager(t_Objeto _tipo,
                                             Gtk::ComboBoxText* cbtext,
                                             Gtk::Button* pAceptar,
                                             Gtk::Button* pGuardarCambios,
                                             Gtk::Button* pEliminar,
                                             const Glib::ustring& def)
: tipo(_tipo),
  nombre_por_defecto(def),
  pModeloActual(NULL),
  comboSelec(cbtext) {
    guardandoCambios = false;

    // botones
    botones[B_ACEPTAR] = pAceptar;
    pAceptar->signal_clicked().connect(sigc::mem_fun(*this,
            &AdminConfigObjManager::on_agregar_button_clicked));
    botones[B_GUARDAR] = pGuardarCambios;
    pGuardarCambios->signal_clicked().connect(sigc::mem_fun(*this,
            &AdminConfigObjManager::on_guardar_cambios_button_clicked));
    botones[B_ELIMINAR] = pEliminar;
    pEliminar->signal_clicked().connect(sigc::mem_fun(*this,
            &AdminConfigObjManager::on_eliminar_button_clicked));

    // combobox
    comboSelec->signal_changed().connect(sigc::mem_fun(*this,
        &AdminConfigObjManager::on_combo_selec_changed));

    pModeloActual = new_modelo();
    mapaConsultasConfiguradas[nombre_por_defecto] = pModeloActual;

    comboSelec->append_text(nombre_por_defecto);
    comboSelec->set_active(0);
}

AdminConfigObjManager::~AdminConfigObjManager() {
    // lo agrego por ser más simple y óptimo iterar sobre una lista que un mapa
    pModeloActual = mapaConsultasConfiguradas[nombre_por_defecto];
    consultasConfiguradas.push_back(pModeloActual);

    std::list< ConfigModelo* >::iterator it = consultasConfiguradas.begin();
    for ( ; it != consultasConfiguradas.end(); ++it) {
        pModeloActual = *it; // para evitar un warning del compilador
        delete pModeloActual;
    }
}
ConfigModelo* AdminConfigObjManager::getModelo() const {
    return pModeloActual;
}
sigc::signal< void, ConfigModelo* > AdminConfigObjManager::signal_model_changed() {
    return _signal_model_changed;
}

#include <iostream>
void AdminConfigObjManager::on_agregar_button_clicked() {
    // pedirle a TabConfigModelo el título de la tab, verificar que no exista para ver si se puede agregar
    // lo que hace TabConfigVista es retornar un modelo nuevo por defecto
    // como la entrada mapaConsultasConfiguradas[NOMBRE_TAB_POR_DEFECTO] ya existe, se pisa ese valor con el nuevo
    // y se agrega la entrada según el nombre en el mapa, en la lista el puntero, y en el combobox ese nombre y se
    // pone como activo
    Glib::ustring tabLabel = pModeloActual->getTabLabelNueva();
    if (mapaConsultasConfiguradas.find(tabLabel) == mapaConsultasConfiguradas.end()) {
        pModeloActual->setTabLabelNuevaComoValida();
        mapaConsultasConfiguradas[tabLabel] = pModeloActual;
        consultasConfiguradas.push_back(pModeloActual);
        comboSelec->append_text(tabLabel);
        comboSelec->set_active_text(tabLabel);
        mapaConsultasConfiguradas[nombre_por_defecto] = new_modelo();
    }
}

void AdminConfigObjManager::on_guardar_cambios_button_clicked() {
    Glib::ustring tabLabelNueva = pModeloActual->getTabLabelNueva();
    // si lo encuentra en el mapa, es porque ya existe y no es válido
    if (mapaConsultasConfiguradas.find(tabLabelNueva) != mapaConsultasConfiguradas.end())
        return;
    if (tabLabelNueva == nombre_por_defecto)
        return;

    guardandoCambios = true;
        int pos = comboSelec->get_active_row_number();
        Glib::ustring labelVieja = pModeloActual->getTabLabel();
        comboSelec->remove_text(labelVieja);
        mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(labelVieja));
        mapaConsultasConfiguradas[tabLabelNueva] = pModeloActual;
        pModeloActual->setTabLabelNuevaComoValida();
        comboSelec->insert_text(pos, tabLabelNueva);
    guardandoCambios = false;
    comboSelec->set_active(pos);

}

void AdminConfigObjManager::on_eliminar_button_clicked() {
    // eliminar modelo seleccionado, remover del mapa, la lista y del combobox
    // busco por el label viejo porque es con el que está en el mapa hasta que se aplican los cambios

    Glib::ustring label = pModeloActual->getTabLabel();
    mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(label));

    std::list< ConfigModelo* >::iterator it = consultasConfiguradas.begin();
    bool encontrado = false;
    while (!encontrado && it != consultasConfiguradas.end())
        encontrado = (*(it++)) == pModeloActual;

    if (encontrado)
        consultasConfiguradas.erase(--it);

    ConfigModelo* bckup = pModeloActual;
    guardandoCambios = true;
        int pos = comboSelec->get_active_row_number();
        comboSelec->remove_text(label);
    guardandoCambios = false;
    comboSelec->set_active(pos-1);
    delete bckup;
}

void AdminConfigObjManager::on_combo_selec_changed() {
    if (guardandoCambios)
        return;
    Glib::ustring tabLabel = comboSelec->get_active_text();
    if (tabLabel == nombre_por_defecto) {
        botones[B_ACEPTAR]->show();
        botones[B_GUARDAR]->hide();
        botones[B_ELIMINAR]->hide();
    } else {
        botones[B_ACEPTAR]->hide();
        botones[B_GUARDAR]->show();
        botones[B_ELIMINAR]->show();
    }

    pModeloActual = mapaConsultasConfiguradas[tabLabel];
    _signal_model_changed.emit(pModeloActual);
}

ConfigModelo* AdminConfigObjManager::new_modelo() {
    switch (tipo) {
        case OBJ_TAB:   return new TabConfigModelo();
        case OBJ_PANEL: return new PanelConfigModelo();
        default: return NULL;
    }
}
