#include "TabConfigModelo.h"

TabConfigModelo::TabConfigModelo()
: tabLabel(NOMBRE_TAB_POR_DEFECTO),
  pEntryTabLabel(NULL),
  pSpinButtonFilas(NULL), pSpinButtonCols(NULL) {
    filas = 1; cols = 1;
    min_fila = 1; min_col = 1;
    for (unsigned i = 0; i < MAX_GRILLA; ++i)
        for (unsigned j = 0; j < MAX_GRILLA; ++j)
            ocupacionesGrilla[i][j] = false;


}

TabConfigModelo::~TabConfigModelo() {

}
#include <iostream>
void TabConfigModelo::desconectar() {
    std::cout << "void TabConfigModelo::desconectar() (@todo)" << std::endl;
    if (pEntryTabLabel)
        connectionEntryTabLabel.disconnect();
    if (pSpinButtonFilas)
        connectionSpinButtonFilas.disconnect();
    if (pSpinButtonCols)
        connectionSpinButtonCols.disconnect();
}

void TabConfigModelo::setEntryTabLabel(Gtk::Entry* pEntry) {
    pEntryTabLabel = pEntry;
    pEntryTabLabel->set_text(tabLabel);
    connectionEntryTabLabel = pEntryTabLabel->signal_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_entry_tab_label_changed));
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

Glib::ustring TabConfigModelo::getTabLabel() const {
    return tabLabel;
}

Glib::ustring TabConfigModelo::getTabLabelNueva() const {
    if (pEntryTabLabel)
        return pEntryTabLabel->get_text();
    else
        return tabLabel;
}

void TabConfigModelo::setTabLabelNuevaComoValida() {
    tabLabel = pEntryTabLabel->get_text();
}

void TabConfigModelo::on_entry_tab_label_changed() {

}

void TabConfigModelo::on_spinbutton_filas_value_changed() {
    filas = pSpinButtonFilas->get_value_as_int();
}

void TabConfigModelo::on_spinbutton_cols_value_changed() {
    cols = pSpinButtonCols->get_value_as_int();
}
