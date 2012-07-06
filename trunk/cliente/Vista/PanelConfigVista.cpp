#include "PanelConfigVista.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "PanelConfigModelo.h"

#define LABEL_POSICION "labelPanelPosicion"
#define SPINBUTTON_DESDE_FILA "spinbuttonPanelDesdeFila"
#define SPINBUTTON_HASTA_FILA "spinbuttonPanelHastaFila"
#define SPINBUTTON_DESDE_COL "spinbuttonPanelDesdeCol"
#define SPINBUTTON_HASTA_COL "spinbuttonPanelHastaCol"
#define HBOX_TIPO_GRAFICO "hboxTipoPanel"
#define EXPANDER_X_PIVOTE "expanderPanelXPivote"
#define EXPANDER_Y_PIVOTE "expanderPanelYPivote"
// macros para los filtradores
#define VBOX_PANEL_FILTROS "vboxPanelFiltros"
#define TOOLBUTTON_PANEL_AGREGAR_FILTRO "toolbuttonPanelAgregarFiltro"
#define VBOX_PANEL_INPUTS "vboxPanelInputs"
#define TOOLBUTTON_PANEL_AGREGAR_INPUT "toolbuttonPanelAgregarInput"
#define VBOX_PANEL_PIVOTE_XS "vboxPanelXPivote"
#define TOOLBUTTON_PANEL_AGREGAR_PIVOTE_X "toolbuttonPanelAgregarXPivote"
#define VBOX_PANEL_PIVOTE_YS "vboxPanelYPivote"
#define TOOLBUTTON_PANEL_AGREGAR_PIVOTE_Y "toolbuttonPanelAgregarYPivote"
#define VBOX_PANEL_RESULTADOS "vboxPanelResultados"
#define TOOLBUTTON_PANEL_AGREGAR_RESULTADO "toolbuttonPanelAgregarResultado"


PanelConfigVista::PanelConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::VBox(cobject), Buildable(_builder), pModelo(NULL) {
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

    // filtradores
    initFiltradores(VBOX_PANEL_FILTROS, pFiltros,
                    TOOLBUTTON_PANEL_AGREGAR_FILTRO, pBotonAgregarFiltro);
    initFiltradores(VBOX_PANEL_INPUTS, pInputs,
                    TOOLBUTTON_PANEL_AGREGAR_INPUT, pBotonAgregarInput);
    initFiltradores(VBOX_PANEL_PIVOTE_XS, pPivoteXs,
                    TOOLBUTTON_PANEL_AGREGAR_PIVOTE_X, pBotonAgregarPivoteX);
    initFiltradores(VBOX_PANEL_PIVOTE_YS, pPivoteYs,
                    TOOLBUTTON_PANEL_AGREGAR_PIVOTE_Y, pBotonAgregarPivoteY);
    initFiltradores(VBOX_PANEL_RESULTADOS, pResultados,
                    TOOLBUTTON_PANEL_AGREGAR_RESULTADO, pBotonAgregarResultado);
}

PanelConfigVista::~PanelConfigVista() {}


void PanelConfigVista::initFiltradores(const Glib::ustring& nombreFilt,
                                       Gtk::VBox*& pFilt,
                                       const Glib::ustring& nombreBoton,
                                       Gtk::ToolButton*& pAgregar) {
    get_widget(nombreFilt, pFilt);
    get_widget(nombreBoton, pAgregar);
}

void PanelConfigVista::setModelo(PanelConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

    if (pModelo)
        pModelo->desconectar();

    pModelo = pModeloNuevo;
    pModelo->setLabelPosicion(pLabelPosicion);
    pModelo->setSpinbuttonsPosicion(pSpinbuttonDesdeFila, pSpinbuttonHastaFila,
                                    pSpinbuttonDesdeCol, pSpinbuttonHastaCol);
    pModelo->setExpandersPivote(pExpanderXPivote, pExpanderYPivote);
    pModelo->setComboboxTipoGrafico(&comboTipoGrafico);

    pModelo->setFiltrosHandlers(filtradoresHandlers(pFiltros, pBotonAgregarFiltro));
    pModelo->setInputsHandlers(filtradoresHandlers(pInputs, pBotonAgregarInput));
    pModelo->setPivoteXsHandlers(filtradoresHandlers(pPivoteXs, pBotonAgregarPivoteX));
    pModelo->setPivoteYsHandlers(filtradoresHandlers(pPivoteYs, pBotonAgregarPivoteY));
    pModelo->setResultadosHandlers(filtradoresHandlers(pResultados, pBotonAgregarResultado));
}



