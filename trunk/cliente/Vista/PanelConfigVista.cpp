#include "PanelConfigVista.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "PanelConfigModelo.h"

#define ENTRY_PANEL_LABEL "entryPanelLabel"
#define LABEL_POSICION "labelPanelPosicion"
#define SPINBUTTON_DESDE_FILA "spinbuttonPanelDesdeFila"
#define SPINBUTTON_HASTA_FILA "spinbuttonPanelHastaFila"
#define SPINBUTTON_DESDE_COL "spinbuttonPanelDesdeCol"
#define SPINBUTTON_HASTA_COL "spinbuttonPanelHastaCol"
#define HBOX_TIPO_GRAFICO "hboxTipoPanel"
#define EXPANDER_X_PIVOTE "expanderPanelXPivote"
#define EXPANDER_Y_PIVOTE "expanderPanelYPivote"

#include <iostream>
PanelConfigVista::PanelConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::VBox(cobject), Buildable(_builder), pModelo(NULL) {
    // label nombre
    get_widget(ENTRY_PANEL_LABEL, pEntryPanelLabel);

    // label posicion
    get_widget(LABEL_POSICION, pLabelPosicion);

    // spinners fila
    get_widget(SPINBUTTON_DESDE_FILA, pSpinbuttonDesdeFila);
    get_widget(SPINBUTTON_HASTA_FILA, pSpinbuttonHastaFila);

    // spinners col
    get_widget(SPINBUTTON_DESDE_COL, pSpinbuttonDesdeCol);
    get_widget(SPINBUTTON_HASTA_COL, pSpinbuttonHastaCol);

    // hbox que contiene el combo de tipo de gráfico
    Gtk::HBox* pHBox;
    get_widget(HBOX_TIPO_GRAFICO, pHBox);
    pHBox->pack_start(comboTipoGrafico, false, false);
    comboTipoGrafico.show();

    // expanders de opciones tabla pivote
    get_widget(EXPANDER_X_PIVOTE, pExpanderXPivote);
    get_widget(EXPANDER_Y_PIVOTE, pExpanderYPivote);
}

PanelConfigVista::~PanelConfigVista() {}

#include <iostream>
void PanelConfigVista::setModelo(PanelConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

//    std::cout << "PanelConfigVista ( " << this << " ) seteando modelo nuevo de panel: " <<pModeloNuevo << std::endl;
    if (pModelo)
        pModelo->desconectar();

    pModelo = pModeloNuevo;
    pModelo->setEntryLabel(pEntryPanelLabel);
    pModelo->setLabelPosicion(pLabelPosicion);
    pModelo->setSpinbuttonsPosicion(pSpinbuttonDesdeFila, pSpinbuttonHastaFila,
                                    pSpinbuttonDesdeCol, pSpinbuttonHastaCol);
    pModelo->setExpandersPivote(pExpanderXPivote, pExpanderYPivote);
    pModelo->setComboboxTipoGrafico(&comboTipoGrafico);
}



