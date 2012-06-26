#include "TabConfigVista.h"
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"
#include "PanelConfigVista.h"
#include "Organizacion.h"

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

#define VBUTTONBOX_TAB_FILTRADORES "vbuttonboxTabFiltradores"

TabConfigVista::TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Table(cobject), Buildable(_builder),
  pModelo(NULL) {
    initBotones();
    initPanelConfig();

    get_widget(ENTRY_TAB_LABEL, pEntryTabLabel);
    get_widget(SPINBUTTON_FILAS, pSpinButtonFilas);
    get_widget(SPINBUTTON_COLS, pSpinButtonCols);

    Gtk::VButtonBox* pFiltradores;
    get_widget(VBUTTONBOX_TAB_FILTRADORES, pFiltradores);
    for (unsigned i = 0; i < Organizacion::cantidadCampos(); ++i) {
        Gtk::CheckButton* p = manage(new Gtk::CheckButton(Organizacion::nombreCampo(i)));
        pCheckButtonsFiltradores.push_back(p);
        pFiltradores->pack_start(*p, false, false);
        p->show();
    }

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
                                botones[BUTTON_AGREGAR_PANEL],
                                botones[BUTTON_GUARDAR_CAMBIOS_PANEL],
                                botones[BUTTON_ELIMINAR_PANEL]
                                );
    on_panel_model_changed(pModelo->getModeloPanel());
    connectionTabModelo = pModelo->signal_panel_model_changed().connect(
        sigc::mem_fun(*this, &TabConfigVista::on_panel_model_changed));
    pModelo->setEntryLabel(pEntryTabLabel);
    pModelo->setSpinButtonsGrilla(pSpinButtonFilas, pSpinButtonCols);

    std::cout << "TabConfigVista " << this << " pasándole al modelo " << this;
    std::list< Gtk::CheckButton* >::iterator it = pCheckButtonsFiltradores.begin();
    for ( ; it != pCheckButtonsFiltradores.end(); ++it)
        std::cout << " " << *it << std::endl;


    pModelo->setCheckButtonsFiltradores(pCheckButtonsFiltradores);
}


void TabConfigVista::on_panel_model_changed(PanelConfigModelo* m) {
//    std::cout << "TabConfigVista ( " << this << " ) recibida la señal de modelo nuevo de panel: " << m << std::endl;
    pPanelVista->setModelo(m);
}
