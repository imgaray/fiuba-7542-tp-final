#include "TabConfigModelo.h"

TabConfigModelo::TabConfigModelo()
: tabLabel(NOMBRE_TAB_POR_DEFECTO),
  pEntryTabLabel(NULL) {
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
}

void TabConfigModelo::setEntryTabLabel(Gtk::Entry* pEntry) {
    pEntryTabLabel = pEntry;
    pEntryTabLabel->set_text(tabLabel);
    connectionEntryTabLabel = pEntryTabLabel->signal_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_entry_tab_label_changed));
}

Glib::ustring TabConfigModelo::getTabLabel() const {
    return tabLabel;
}

void TabConfigModelo::on_entry_tab_label_changed() {
    tabLabel = pEntryTabLabel->get_text();
}
