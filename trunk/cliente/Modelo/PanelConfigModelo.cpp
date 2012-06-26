#include "PanelConfigModelo.h"

PanelConfigModelo::PanelConfigModelo()
: ConfigModelo(NOMBRE_PANEL_POR_DEFECTO) {

}

PanelConfigModelo::~PanelConfigModelo() {
    desconectar();
}

void PanelConfigModelo::desconectarDeHijo() {

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


}
