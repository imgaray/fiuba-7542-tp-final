#include "TabConfigModelo.h"

TabConfigModelo::TabConfigModelo()
: ConfigModelo(NOMBRE_TAB_POR_DEFECTO),
  pSpinButtonFilas(NULL), pSpinButtonCols(NULL) {
    filas = 1; cols = 1;
    min_fila = 1; min_col = 1;
    for (unsigned i = 0; i < MAX_GRILLA; ++i)
        for (unsigned j = 0; j < MAX_GRILLA; ++j)
            ocupacionesGrilla[i][j] = false;
}

TabConfigModelo::~TabConfigModelo() {
    desconectar();
}

#include <iostream>
void TabConfigModelo::desconectarDeHijo() {
    if (pSpinButtonFilas) {
        connectionSpinButtonFilas.disconnect();
        pSpinButtonFilas = NULL;
    }
    if (pSpinButtonCols) {
        connectionSpinButtonCols.disconnect();
        pSpinButtonCols = NULL;
    }
}

void TabConfigModelo::setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                           Gtk::SpinButton* pCols) {
    pSpinButtonFilas = pFilas;
    pSpinButtonCols = pCols;
    pSpinButtonFilas->set_value(filas);
    pSpinButtonCols->set_value(cols);
    pSpinButtonFilas->get_adjustment()->set_lower(min_fila);
    pSpinButtonCols->get_adjustment()->set_lower(min_col);

    connectionSpinButtonFilas = pSpinButtonFilas->signal_value_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_spinbutton_filas_value_changed));
    connectionSpinButtonCols = pSpinButtonCols->signal_value_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_spinbutton_cols_value_changed));
}

void TabConfigModelo::on_spinbutton_filas_value_changed() {
    filas = pSpinButtonFilas->get_value_as_int();
}

void TabConfigModelo::on_spinbutton_cols_value_changed() {
    cols = pSpinButtonCols->get_value_as_int();
}
