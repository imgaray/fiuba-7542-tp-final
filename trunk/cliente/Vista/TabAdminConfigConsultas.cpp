#include "TabAdminConfigConsultas.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "TabConfigVista.h"
#include "AdminConfigObjManager.h"

// botones
#define BUTTON_AGREGAR_TAB "buttonAgregarTab"
#define BUTTON_GUARDAR_CAMBIOS_TAB "buttonGuardarCambiosTab"
#define BUTTON_ELIMINAR_TAB "buttonEliminarTab"

// config tabs
#define HBOX_TAB_SELEC "hboxTabSelec"
#define TABLE_TAB_CONFIG "tableTabConfig"

#include <iostream>
TabAdminConfigConsultas::TabAdminConfigConsultas(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder) {
    initBotones();
    initTabConfig();
    objManager = new AdminConfigObjManager(OBJ_TAB,
                                           &comboTabSelec,
                                           botones[BUTTON_AGREGAR_TAB],
                                           botones[BUTTON_GUARDAR_CAMBIOS_TAB],
                                           botones[BUTTON_ELIMINAR_TAB],
                                           NOMBRE_TAB_POR_DEFECTO
                                           );
    on_tab_model_changed(objManager->getModelo());
    objManager->signal_model_changed().connect(sigc::mem_fun(*this,
        &TabAdminConfigConsultas::on_tab_model_changed));
}

TabAdminConfigConsultas::~TabAdminConfigConsultas() {
    delete objManager;
}

void TabAdminConfigConsultas::initBotones() {
    Gtk::Button* pAux;
    builder->get_widget(BUTTON_AGREGAR_TAB, pAux);
    if (pAux)
        botones[BUTTON_AGREGAR_TAB] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_AGREGAR_TAB);

    builder->get_widget(BUTTON_GUARDAR_CAMBIOS_TAB, pAux);
    if (pAux)
        botones[BUTTON_GUARDAR_CAMBIOS_TAB] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_GUARDAR_CAMBIOS_TAB);

    builder->get_widget(BUTTON_ELIMINAR_TAB, pAux);
    if (pAux)
        botones[BUTTON_ELIMINAR_TAB] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_ELIMINAR_TAB);
}

void TabAdminConfigConsultas::initTabConfig() {
    builder->get_widget_derived(TABLE_TAB_CONFIG, pTabVista);
    if (!pTabVista)
        throw ExcepcionArchivoGladeCorrupto(TABLE_TAB_CONFIG);

    Gtk::HBox* pHBoxTabSelec;
    builder->get_widget(HBOX_TAB_SELEC, pHBoxTabSelec);
    if (pHBoxTabSelec) {
        pHBoxTabSelec->pack_start(comboTabSelec, false, false);
        comboTabSelec.show();
    } else
        throw ExcepcionArchivoGladeCorrupto(HBOX_TAB_SELEC);
}

void TabAdminConfigConsultas::on_tab_model_changed(ConfigModelo* m) {
    std::cout << "TabAdminConfigConsultas( "<<this << " ) recibida la señal de modelo nuevo ";
    TabConfigModelo* mTab = dynamic_cast< TabConfigModelo* >(m);
    if (mTab) {
        std::cout << "de tab: " << mTab << std::endl;
        pTabVista->setModelo(mTab);
    }
    else
        throw "Vista y modelo incompatibles";
}

bool TabAdminConfigConsultas::aplicarCambios() {
    std::cout << "bool TabAdminConfigConsultas::aplicarCambios()... guardando en archivo (@todo)" << std::endl;
    return true;
}