#include "PanelConfigModelo.h"
#include "FiltradorConfigManager.h"
#include "Panel.h"
#include "TablaComun.h"
#include "TablaPivote.h"
#include "GraficoDeTorta.h"
#include "GraficoDeBarras.h"
#include <iostream>

#include <gtkmm-2.4/gtkmm/spinbutton.h>

#define LABEL_POSICION "Posición en la grilla"
#define ERROR " - Error"

#define TABLA   0
#define PIVOTE  1
#define BARRAS  2
#define TORTA   3
#define CANT_TIPOS 4


//Defines para Xml
#define NOMBRE_NODO "Panel_Config_Modelo"
#define ATR_NOMBRE "atr_nombre"
#define ATR_TIPO_GRAF "atr_tipo_graf"

#define ATR_DESDE_FILA "atr_desde_fila"
#define ATR_DESDE_COL "atr_desde_col"
#define ATR_HASTA_FILA "atr_hasta_fila"
#define ATR_HASTA_COL "atr_hasta_col"


#define HIJO_FILTROS "hijos_filtros"
#define HIJO_INPUTS "hijo_inputs"
#define HIJO_X_PIV "hijo_x_piv"
#define HIJO_Y_PIV "hijo_y_piv"
#define HIJO_RES "hijo_res"

Glib::ustring PanelConfigModelo::tiposGrafico[CANT_TIPOS] = {
    "Tabla", "Tabla pivote", "Gráfico de barras", "Gráfico de torta"
};

PanelConfigModelo::PanelConfigModelo()
: ConfigModelo(NOMBRE_PANEL_POR_DEFECTO),
  filtrosManager(NULL), inputsManager(NULL),
  pivoteXsManager(NULL), pivoteYsManager(NULL),
  resutadosManager(NULL),
  pLabelPosicion(NULL),
  pSpinButtonDesdeFila(NULL), pSpinButtonHastaFila(NULL),
  pSpinButtonDesdeCol(NULL), pSpinButtonHastaCol(NULL),
  pComboBoxTextTipoGrafico(NULL),
  pExpanderXPivote(NULL), pExpanderYPivote(NULL) {

    desdeFila = 0; hastaFila = 1;
    desdeCol = 0; hastaCol = 1;
    posicionValida = true;
    indice_tipoGrafico = TABLA;

    posicionesDeserializadas = true;
}

PanelConfigModelo::~PanelConfigModelo() {
    desconectar();
    delete filtrosManager;
    delete inputsManager;
    delete pivoteXsManager;
    delete pivoteYsManager;
    delete resutadosManager;
}

void PanelConfigModelo::desconectarDeHijo() {
    if (filtrosManager)
        filtrosManager->desconectar();
    if (inputsManager)
        inputsManager->desconectar();
    if (pivoteXsManager)
        pivoteXsManager->desconectar();
    if (pivoteYsManager)
        pivoteYsManager->desconectar();
    if (resutadosManager)
        resutadosManager->desconectar();

    desconectar(connectionSpinButtonDesdeFila, pSpinButtonDesdeFila);
    desconectar(connectionSpinButtonHastaFila, pSpinButtonHastaFila);
    desconectar(connectionSpinButtonDesdeCol, pSpinButtonDesdeCol);
    desconectar(connectionSpinButtonHastaCol, pSpinButtonHastaCol);
    desconectar(connectionComboboxTipoGrafico, pComboBoxTextTipoGrafico);
}

void PanelConfigModelo::bloquearConnectionPosicion() {
    connectionSpinButtonDesdeFila.block();
    connectionSpinButtonHastaFila.block();
    connectionSpinButtonDesdeCol.block();
    connectionSpinButtonHastaCol.block();
}

void PanelConfigModelo::desbloquearConnectionPosicion() {
    connectionSpinButtonDesdeFila.unblock();
    connectionSpinButtonHastaFila.unblock();
    connectionSpinButtonDesdeCol.unblock();
    connectionSpinButtonHastaCol.unblock();
}

void PanelConfigModelo::setPosicionNuevaComoValida(bool valida) {
    posicionValida = valida;

    if (posicionValida) {
        if (pSpinButtonDesdeFila)
            desdeFila = pSpinButtonDesdeFila->get_value_as_int();
        if (pSpinButtonHastaFila)
            hastaFila = pSpinButtonHastaFila->get_value_as_int();
        if (pSpinButtonDesdeCol)
            desdeCol = pSpinButtonDesdeCol->get_value_as_int();
        if (pSpinButtonHastaCol)
            hastaCol = pSpinButtonHastaCol->get_value_as_int();
        if (pLabelPosicion)
            pLabelPosicion->set_text(LABEL_POSICION);
    } else
        if (pLabelPosicion)
            pLabelPosicion->set_text(LABEL_POSICION ERROR);
}

void PanelConfigModelo::getPosicion(int& _desdeFila, int& _hastaFila,
                                    int& _desdeCol, int& _hastaCol) {
    _desdeFila = desdeFila;
    _hastaFila = hastaFila;
    _desdeCol = desdeCol;
    _hastaCol = hastaCol;
}

sigc::signal< void, PanelConfigModelo*, int, int, int, int >
    PanelConfigModelo::signal_posicion_changed() {
    return _signal_posicion_changed;
}

void PanelConfigModelo::setLabelPosicion(Gtk::Label* pLabel) {
    pLabelPosicion = pLabel;
    if (posicionValida)
        pLabelPosicion->set_text(LABEL_POSICION);
    else
        pLabelPosicion->set_text(LABEL_POSICION ERROR);
}

void PanelConfigModelo::setSpinbuttonsPosicion(
    Gtk::SpinButton* _pSpinButtonDesdeFila,
    Gtk::SpinButton* _pSpinButtonHastaFila,
    Gtk::SpinButton* _pSpinButtonDesdeCol,
    Gtk::SpinButton* _pSpinButtonHastaCol) {

    pSpinButtonDesdeFila = _pSpinButtonDesdeFila;
    pSpinButtonHastaFila = _pSpinButtonHastaFila;
    pSpinButtonDesdeCol = _pSpinButtonDesdeCol;
    pSpinButtonHastaCol = _pSpinButtonHastaCol;

    pSpinButtonDesdeFila->set_value(desdeFila);
    pSpinButtonHastaFila->set_value(hastaFila);
    pSpinButtonDesdeCol->set_value(desdeCol);
    pSpinButtonHastaCol->set_value(hastaCol);

    connectionSpinButtonDesdeFila = pSpinButtonDesdeFila->signal_value_changed().connect(
        sigc::mem_fun(*this, &PanelConfigModelo::on_spinbuttons_posicion_changed));
    connectionSpinButtonHastaFila = pSpinButtonHastaFila->signal_value_changed().connect(
        sigc::mem_fun(*this, &PanelConfigModelo::on_spinbuttons_posicion_changed));
    connectionSpinButtonDesdeCol = pSpinButtonDesdeCol->signal_value_changed().connect(
        sigc::mem_fun(*this, &PanelConfigModelo::on_spinbuttons_posicion_changed));
    connectionSpinButtonHastaCol = pSpinButtonHastaCol->signal_value_changed().connect(
        sigc::mem_fun(*this, &PanelConfigModelo::on_spinbuttons_posicion_changed));
}

void PanelConfigModelo::setComboboxTipoGrafico(Gtk::ComboBoxText* pCombo) {
    if (pCombo->get_active_text() == "")
        for (int i = 0; i < CANT_TIPOS; ++i)
            pCombo->append_text(tiposGrafico[i]);

    pComboBoxTextTipoGrafico = pCombo;
    connectionComboboxTipoGrafico = pComboBoxTextTipoGrafico->signal_changed().connect(
        sigc::mem_fun(*this, &PanelConfigModelo::on_combobox_tipo_grafico_changed));
    pComboBoxTextTipoGrafico->set_active(indice_tipoGrafico);
}

void PanelConfigModelo::setExpandersPivote(Gtk::Expander* pXPivote,
                                           Gtk::Expander* pYPivote) {
    pExpanderXPivote = pXPivote;
    pExpanderYPivote = pYPivote;
}


void PanelConfigModelo::setFiltrosHandlers(const filtradoresHandlers& handlers) {
    if (!filtrosManager)
        filtrosManager = new FiltradorConfigManager(FILT_FILTRO, handlers);
    else
        filtrosManager->reconectar();
}

void PanelConfigModelo::setInputsHandlers(const filtradoresHandlers& handlers) {
    if (!inputsManager)
        inputsManager = new FiltradorConfigManager(FILT_INPUT, handlers);
    else
        inputsManager->reconectar();
}

void PanelConfigModelo::setPivoteXsHandlers(const filtradoresHandlers& handlers) {
    if (!pivoteXsManager)
        pivoteXsManager = new FiltradorConfigManager(FILT_PIVOTE_X, handlers);
    else
        pivoteXsManager->reconectar();
}

void PanelConfigModelo::setPivoteYsHandlers(const filtradoresHandlers& handlers) {
    if (!pivoteYsManager)
        pivoteYsManager = new FiltradorConfigManager(FILT_PIVOTE_Y, handlers);
    else
        pivoteYsManager->reconectar();
}

void PanelConfigModelo::setResultadosHandlers(const filtradoresHandlers& handlers) {
    if (!resutadosManager)
        resutadosManager = new FiltradorConfigManager(FILT_RESULTADO, handlers);
    else
        resutadosManager->reconectar();
}

Panel* PanelConfigModelo::concretarConfig(FiltradoresPanel* filtPanel) {
    // crear el panel
    Panel* panel = manage(new Panel(getLabel()));

    // cargar el conjunto de filtradores
    filtrosManager->setFiltradoresEn(filtPanel);
    inputsManager->setFiltradoresEn(filtPanel);
    if (indice_tipoGrafico == PIVOTE) {
        pivoteXsManager->setFiltradoresEn(filtPanel);
        pivoteYsManager->setFiltradoresEn(filtPanel);
    }
    resutadosManager->setFiltradoresEn(filtPanel);

    // crear el gráfico y agregarlo al panel
    Tabla* tabla;
    Grafico* grafico;
    switch (indice_tipoGrafico) {
        case TABLA:     tabla = manage(new TablaComun(filtPanel));
                        panel->setContenido(*tabla);
                        break;
        case PIVOTE:    tabla = manage(new TablaPivote(filtPanel));
                        panel->setContenido(*tabla);
                        break;
        case BARRAS:    grafico = manage(new GraficoDeBarras(filtPanel));
                        panel->setContenido(*grafico);
                        break;
        case TORTA:     grafico = manage(new GraficoDeTorta(filtPanel));
                        panel->setContenido(*grafico);
                        break;
        default: break;
    }

    return panel;
}

void PanelConfigModelo::on_spinbuttons_posicion_changed() {
	if (posicionesDeserializadas == false)
		return;

    bloquearConnectionPosicion();

    int desdeFilaNuevo = pSpinButtonDesdeFila->get_value_as_int();
    int hastaFilaNuevo = pSpinButtonHastaFila->get_value_as_int();
    int desdeColNuevo = pSpinButtonDesdeCol->get_value_as_int();
    int hastaColNuevo = pSpinButtonHastaCol->get_value_as_int();

    if (desdeFilaNuevo == hastaFilaNuevo)
        if (pSpinButtonHastaFila->get_adjustment()->get_upper() > hastaFilaNuevo)
            pSpinButtonHastaFila->set_value(hastaFilaNuevo+1);
        else
            pSpinButtonDesdeFila->set_value(desdeFilaNuevo-1);
    else if (desdeFilaNuevo > hastaFilaNuevo)
        // mantener la diferencia de la última posición válida
        pSpinButtonHastaFila->set_value(hastaFilaNuevo + hastaFila-desdeFila);

    if (desdeColNuevo == hastaColNuevo)
        if (pSpinButtonHastaCol->get_adjustment()->get_upper() > hastaColNuevo)
            pSpinButtonHastaCol->set_value(hastaColNuevo+1);
        else
            pSpinButtonDesdeCol->set_value(desdeColNuevo-1);
    else if (desdeColNuevo > hastaColNuevo)
        // mantener la diferencia de la última posición válida
        pSpinButtonHastaCol->set_value(hastaColNuevo + hastaCol-desdeCol);

    desdeFilaNuevo = pSpinButtonDesdeFila->get_value_as_int();
    hastaFilaNuevo = pSpinButtonHastaFila->get_value_as_int();
    desdeColNuevo = pSpinButtonDesdeCol->get_value_as_int();
    hastaColNuevo = pSpinButtonHastaCol->get_value_as_int();

    _signal_posicion_changed.emit(this,
                                  desdeFilaNuevo, hastaFilaNuevo,
                                  desdeColNuevo, hastaColNuevo);

    desbloquearConnectionPosicion();
}

void PanelConfigModelo::on_combobox_tipo_grafico_changed() {
    indice_tipoGrafico = pComboBoxTextTipoGrafico->get_active_row_number();
    if (indice_tipoGrafico == PIVOTE) {
        pExpanderXPivote->show();
        pExpanderYPivote->show();
    } else {
        pExpanderXPivote->hide();
        pExpanderYPivote->hide();
    }
}

NodoXml PanelConfigModelo::serializar(){
	NodoXml nodo(NOMBRE_NODO);

	nodo.SetAttribute(ATR_DESDE_FILA, this->desdeFila);
	nodo.SetAttribute(ATR_HASTA_FILA, this->hastaFila);

	nodo.SetAttribute(ATR_DESDE_COL, this->desdeCol);
	nodo.SetAttribute(ATR_HASTA_COL, this->hastaCol);

	nodo.SetAttribute(ATR_TIPO_GRAF, this->indice_tipoGrafico);
	nodo.SetAttribute(ATR_NOMBRE, this->getLabel().c_str());

	NodoXml nodoFiltros(filtrosManager->serializar());
	nodoFiltros.SetValue(HIJO_FILTROS);
	nodo.InsertEndChild(nodoFiltros);

	NodoXml nodoInputs(inputsManager->serializar());
	nodoInputs.SetValue(HIJO_INPUTS);
	nodo.InsertEndChild(nodoInputs);

	NodoXml nodoXP(pivoteXsManager->serializar());
	nodoXP.SetValue(HIJO_X_PIV);
	nodo.InsertEndChild(nodoXP);

	NodoXml nodoYP(pivoteYsManager->serializar());
	nodoYP.SetValue(HIJO_Y_PIV);
	nodo.InsertEndChild(nodoYP);

	NodoXml nodoRes(resutadosManager->serializar());
	nodoRes.SetValue(HIJO_RES);
	nodo.InsertEndChild(nodoRes);

	return nodo;
}

void PanelConfigModelo::deserializar(const NodoXml& nodo){

	// @todo cargar nombre

	posicionesDeserializadas = false;

	if (nodo.Attribute(ATR_NOMBRE) != NULL) {
		this->setLabel(nodo.Attribute(ATR_NOMBRE));
	}
	else {
		throw ErrorSerializacionXML();
	}

	bool infoOK = true;

	infoOK = infoOK && nodo.Attribute(ATR_DESDE_FILA, &this->desdeFila);
	infoOK = infoOK && nodo.Attribute(ATR_HASTA_FILA, &this->hastaFila);
	infoOK = infoOK && nodo.Attribute(ATR_DESDE_COL, &this->desdeCol);
	infoOK = infoOK && nodo.Attribute(ATR_HASTA_COL, &this->hastaCol);

	infoOK = infoOK && nodo.Attribute(ATR_TIPO_GRAF, &this->indice_tipoGrafico);

	if (infoOK == false) {
		throw ErrorSerializacionXML();
	}


	if (this->pSpinButtonDesdeCol) {
		this->pSpinButtonDesdeCol->set_value(desdeCol);

	}

	if (this->pSpinButtonDesdeFila) {
		this->pSpinButtonDesdeFila->set_value(desdeFila);
	}

	if (this->pSpinButtonHastaCol) {
		this->pSpinButtonHastaCol->set_value(hastaCol);
	}

	if (this->pSpinButtonHastaFila) {
		this->pSpinButtonHastaFila->set_value(hastaFila);
	}


	posicionesDeserializadas = true;


	this->pComboBoxTextTipoGrafico->set_active(indice_tipoGrafico);

	const NodoXml *hijo = NULL;

	// Deserializo el Filtros
	hijo = nodo.FirstChildElement(HIJO_FILTROS);
	if (hijo != NULL)
		filtrosManager->deserializar(*hijo);
	else
		throw ErrorSerializacionXML();

	// Deserializos los Inputs
	hijo = nodo.FirstChildElement(HIJO_INPUTS);
	if (hijo != NULL)
		inputsManager->deserializar(*hijo);
	else
		throw ErrorSerializacionXML();

    if (indice_tipoGrafico == PIVOTE) {
        // Deserializos el grupo X de la Tabla Pivote

        hijo = nodo.FirstChildElement(HIJO_X_PIV);
        if (hijo != NULL)
            pivoteXsManager->deserializar(*hijo);
        else
            throw ErrorSerializacionXML();

        // Deserializo el grupo Y de la Tabla Pivote

        hijo = nodo.FirstChildElement(HIJO_Y_PIV);
        if (hijo != NULL)
            pivoteYsManager->deserializar(*hijo);
        else
            throw ErrorSerializacionXML();
    }

	// Deserializo los resultados
	hijo = nodo.FirstChildElement(HIJO_RES);
	if (hijo != NULL)
		resutadosManager->deserializar(*hijo);
	else
		throw ErrorSerializacionXML();
}
