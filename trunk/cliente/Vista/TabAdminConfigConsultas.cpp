#include "TabAdminConfigConsultas.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "TabConfigVista.h"
#include "AdminConfigObjManager.h"
#include "VentanaClienteDinamica.h"
#include "DefinicionesXML.h"

// botones
#define BUTTON_AGREGAR_TAB "buttonAgregarTab"
#define BUTTON_GUARDAR_CAMBIOS_TAB "buttonGuardarCambiosTab"
#define BUTTON_ELIMINAR_TAB "buttonEliminarTab"

// config tabs
#define HBOX_TAB_SELEC "hboxTabSelec"
#define VBOX_TAB_CONFIG "vboxTabConfig"
#define ENTRY_TAB_LABEL "entryTabLabel"

#include <iostream>
TabAdminConfigConsultas::TabAdminConfigConsultas(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder) {
    initBotones();
    initTabConfig();
    tabManager = new AdminConfigObjManager(OBJ_TAB,
                                           &comboTabSelec,
                                           pEntryTabLabel,
                                           botones[BUTTON_AGREGAR_TAB],
                                           botones[BUTTON_GUARDAR_CAMBIOS_TAB],
                                           botones[BUTTON_ELIMINAR_TAB],
                                           NOMBRE_TAB_POR_DEFECTO
                                           );
    on_tab_model_changed(tabManager->getModelo());
    tabManager->signal_model_changed().connect(sigc::mem_fun(*this,
        &TabAdminConfigConsultas::on_tab_model_changed));
}

TabAdminConfigConsultas::~TabAdminConfigConsultas() {
    delete tabManager;
}

void TabAdminConfigConsultas::initBotones() {
    Gtk::Button* pAux;
    get_widget(BUTTON_AGREGAR_TAB, pAux);
    botones[BUTTON_AGREGAR_TAB] = pAux;

    get_widget(BUTTON_GUARDAR_CAMBIOS_TAB, pAux);
    botones[BUTTON_GUARDAR_CAMBIOS_TAB] = pAux;

    get_widget(BUTTON_ELIMINAR_TAB, pAux);
    botones[BUTTON_ELIMINAR_TAB] = pAux;
}

void TabAdminConfigConsultas::initTabConfig() {
    get_widget(ENTRY_TAB_LABEL, pEntryTabLabel);
    get_widget_derived(VBOX_TAB_CONFIG, pTabVista);

    Gtk::HBox* pHBoxTabSelec;
    get_widget(HBOX_TAB_SELEC, pHBoxTabSelec);
    pHBoxTabSelec->pack_start(comboTabSelec, false, false);
    comboTabSelec.show();
}

void TabAdminConfigConsultas::setArchivoPersonalizador(const char* archivo) {
    this->cargarConsultas(archivo);
    dynBuilder.construir(tabManager);
}

void TabAdminConfigConsultas::actualizarVDinamica(
    VentanaClienteDinamica* pVDinamica) {
    pVDinamica->personalizar(dynBuilder);
}

void TabAdminConfigConsultas::on_tab_model_changed(ConfigModelo* m) {
    TabConfigModelo* mTab = dynamic_cast< TabConfigModelo* >(m);
    if (mTab) {
        pEntryTabLabel->set_text(mTab->getLabel());
        pTabVista->setModelo(mTab);
    } else
        throw "Vista y modelo incompatibles";
}

bool TabAdminConfigConsultas::aplicarCambios() {
    //std::cout << "bool TabAdminConfigConsultas::aplicarCambios()... (@todo)" << std::endl;
    dynBuilder.construir(tabManager);

    TiXmlDocument docXml(rutaArchivo.c_str());

    docXml.InsertEndChild(tabManager->serializar());

    // @todo ver otra forma de mostrar este error
    if (docXml.SaveFile() == false) {
    	std::cout << "Error al guardar en XML: ";
    	std::cout << docXml.ErrorDesc() << std::endl;
    }

    return true;
}

void TabAdminConfigConsultas::cargarConsultas(const char* ruta) {
	rutaArchivo = ruta;
	TiXmlDocument docXml(ruta);
	docXml.LoadFile();
	if (docXml.RootElement() != NULL) {
		tabManager->deserializar(*docXml.RootElement());
	}
}
