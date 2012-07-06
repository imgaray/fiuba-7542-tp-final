#include "TabConfigVista.h"
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "PanelConfigVista.h"
#include "PanelConfigModelo.h"
#include "Organizacion.h"

// botones
#define BUTTON_AGREGAR_PANEL "buttonAgregarPanel"
#define BUTTON_GUARDAR_CAMBIOS_PANEL "buttonGuardarCambiosPanel"
#define BUTTON_ELIMINAR_PANEL "buttonEliminarPanel"

// config panels
#define HBOX_PANEL_SELEC "hboxPanelSelec"
#define VBOX_PANEL_CONFIG "vboxPanelConfig"
#define ENTRY_PANEL_LABEL "entryPanelLabel"

#define SPINBUTTON_FILAS "spinbuttonFilas"
#define SPINBUTTON_COLS "spinbuttonCols"

#define VBOX_TAB_INPUTS "vboxTabInputs"
#define TOOLBUTTON_TAB_AGREGAR_INPUT "toolbuttonTabAgregarInput"

TabConfigVista::TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Table(cobject), Buildable(_builder),
  pModelo(NULL) {
    initBotones();
    initPanelConfig();

    get_widget(SPINBUTTON_FILAS, pSpinButtonFilas);
    get_widget(SPINBUTTON_COLS, pSpinButtonCols);

    get_widget(VBOX_TAB_INPUTS, pInputs);
    get_widget(TOOLBUTTON_TAB_AGREGAR_INPUT, pBotonAgregarInput);
}

TabConfigVista::~TabConfigVista() {

}

void TabConfigVista::initBotones() {
    Gtk::Button* pAux;
    get_widget(BUTTON_AGREGAR_PANEL, pAux);
    botones[BUTTON_AGREGAR_PANEL] = pAux;

    get_widget(BUTTON_GUARDAR_CAMBIOS_PANEL, pAux);
    botones[BUTTON_GUARDAR_CAMBIOS_PANEL] = pAux;

    get_widget(BUTTON_ELIMINAR_PANEL, pAux);
    botones[BUTTON_ELIMINAR_PANEL] = pAux;
}

void TabConfigVista::initPanelConfig() {
    get_widget(ENTRY_PANEL_LABEL, pEntryPanelLabel);
    get_widget_derived(VBOX_PANEL_CONFIG, pPanelVista);

    Gtk::HBox* pHBoxPanelSelec;
    get_widget(HBOX_PANEL_SELEC, pHBoxPanelSelec);
    pHBoxPanelSelec->pack_start(comboPanelSelec, false, false);
    comboPanelSelec.show();
}

#include <iostream>
void TabConfigVista::setModelo(TabConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

    if (pModelo)
        pModelo->desconectar();

//    std::cout << "TabConfigVista ( " << this << " ) seteando modelo nuevo de tab: " <<pModeloNuevo << std::endl;
    pModelo = pModeloNuevo;
    pModelo->setObjManagerPanel(&comboPanelSelec,
                                pEntryPanelLabel,
                                botones[BUTTON_AGREGAR_PANEL],
                                botones[BUTTON_GUARDAR_CAMBIOS_PANEL],
                                botones[BUTTON_ELIMINAR_PANEL]
                                );
    on_panel_model_changed(pModelo->getModeloPanel());
    connectionTabModelo = pModelo->signal_panel_model_changed().connect(
        sigc::mem_fun(*this, &TabConfigVista::on_panel_model_changed));
    pModelo->setSpinButtonsGrilla(pSpinButtonFilas, pSpinButtonCols);
    pModelo->setInputsHandlers(filtradoresHandlers(pInputs, pBotonAgregarInput));
}


void TabConfigVista::on_panel_model_changed(PanelConfigModelo* m) {
    pEntryPanelLabel->set_text(m->getLabel());
    pPanelVista->setModelo(m);
}
