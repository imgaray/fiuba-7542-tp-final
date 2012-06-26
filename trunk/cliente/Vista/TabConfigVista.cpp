#include "TabConfigVista.h"
#include <gtkmm/box.h>
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "PanelConfigVista.h"

// botones
#define BUTTON_AGREGAR_PANEL "buttonAgregarPanel"
#define BUTTON_GUARDAR_CAMBIOS_PANEL "buttonGuardarCambiosPanel"
#define BUTTON_ELIMINAR_PANEL "buttonEliminarPanel"

// config panels
#define HBOX_PANEL_SELEC "hboxPanelSelec"
#define VBOX_PANEL_CONFIG "vboxPanelConfig"

#define ENTRY_TAB_LABEL "entryTabLabel"
#define SPINBUTTON_FILAS "spinbuttonFilas"
#define SPINBUTTON_COLS "spinbuttonCols"

TabConfigVista::TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Table(cobject), builder(_builder), pModelo(NULL) {
    initBotones();
    initPanelConfig();
    builder->get_widget(ENTRY_TAB_LABEL, pEntryTabLabel);
    if (!pEntryTabLabel)
        throw ExcepcionArchivoGladeCorrupto(ENTRY_TAB_LABEL);

    builder->get_widget(SPINBUTTON_FILAS, pSpinButtonFilas);
    if (!pSpinButtonFilas)
        throw ExcepcionArchivoGladeCorrupto(SPINBUTTON_FILAS);

    builder->get_widget(SPINBUTTON_COLS, pSpinButtonCols);
    if (!pSpinButtonCols)
        throw ExcepcionArchivoGladeCorrupto(SPINBUTTON_COLS);

}

TabConfigVista::~TabConfigVista() {

}

void TabConfigVista::initBotones() {
    Gtk::Button* pAux;
    builder->get_widget(BUTTON_AGREGAR_PANEL, pAux);
    if (pAux)
        botones[BUTTON_AGREGAR_PANEL] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_AGREGAR_PANEL);

    builder->get_widget(BUTTON_GUARDAR_CAMBIOS_PANEL, pAux);
    if (pAux)
        botones[BUTTON_GUARDAR_CAMBIOS_PANEL] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_GUARDAR_CAMBIOS_PANEL);

    builder->get_widget(BUTTON_ELIMINAR_PANEL, pAux);
    if (pAux)
        botones[BUTTON_ELIMINAR_PANEL] = pAux;
    else
        throw ExcepcionArchivoGladeCorrupto(BUTTON_ELIMINAR_PANEL);
}

void TabConfigVista::initPanelConfig() {
    builder->get_widget_derived(VBOX_PANEL_CONFIG, pPanelVista);
    if (!pPanelVista)
        throw ExcepcionArchivoGladeCorrupto(VBOX_PANEL_CONFIG);

    Gtk::HBox* pHBoxPanelSelec;
    builder->get_widget(HBOX_PANEL_SELEC, pHBoxPanelSelec);
    if (pHBoxPanelSelec) {
        pHBoxPanelSelec->pack_start(comboPanelSelec, false, false);
        comboPanelSelec.show();
    } else
        throw ExcepcionArchivoGladeCorrupto(HBOX_PANEL_SELEC);

}

#include <iostream>
void TabConfigVista::setModelo(TabConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

    if (pModelo)
        pModelo->desconectar();

    std::cout << "TabConfigVista ( " << this << " ) seteando modelo nuevo de tab: " <<pModeloNuevo << std::endl;
    pModelo = pModeloNuevo;
    pModelo->setObjManagerPanel(&comboPanelSelec,
                                botones[BUTTON_AGREGAR_PANEL],
                                botones[BUTTON_GUARDAR_CAMBIOS_PANEL],
                                botones[BUTTON_ELIMINAR_PANEL]
                                );
    on_panel_model_changed(pModelo->getModeloPanel());
    connectionTabModelo = pModelo->signal_panel_model_changed().connect(
        sigc::mem_fun(*this, &TabConfigVista::on_panel_model_changed));
    pModelo->setEntryLabel(pEntryTabLabel);
    pModelo->setSpinButtonsGrilla(pSpinButtonFilas, pSpinButtonCols);
}


void TabConfigVista::on_panel_model_changed(PanelConfigModelo* m) {
    std::cout << "TabConfigVista ( " << this << " ) recibida la señal de modelo nuevo de panel: " << m << std::endl;
    pPanelVista->setModelo(m);
}
