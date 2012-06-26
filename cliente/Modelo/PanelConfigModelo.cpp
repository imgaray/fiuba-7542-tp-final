#include "PanelConfigModelo.h"

#define LABEL_POSICION "Posición en la grilla"
#define ERROR " - Error"

PanelConfigModelo::PanelConfigModelo()
: ConfigModelo(NOMBRE_PANEL_POR_DEFECTO),
  pLabelPosicion(NULL),
  pSpinButtonDesdeFila(NULL), pSpinButtonHastaFila(NULL),
  pSpinButtonDesdeCol(NULL), pSpinButtonHastaCol(NULL) {
    desdeFila = 0; hastaFila = 1;
    desdeCol = 0; hastaCol = 1;
    posicionValida = true;
}

PanelConfigModelo::~PanelConfigModelo() {
    desconectar();
}

void PanelConfigModelo::desconectarDeHijo() {
    desconectar(connectionSpinButtonDesdeFila, pSpinButtonDesdeFila);
    desconectar(connectionSpinButtonHastaFila, pSpinButtonHastaFila);
    desconectar(connectionSpinButtonDesdeCol, pSpinButtonDesdeCol);
    desconectar(connectionSpinButtonHastaCol, pSpinButtonHastaCol);
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

void PanelConfigModelo::getPosicion(unsigned& _desdeFila, unsigned& _hastaFila,
                                    unsigned& _desdeCol, unsigned& _hastaCol) {
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

void PanelConfigModelo::on_spinbuttons_posicion_changed() {
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

