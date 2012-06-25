#include "ConfigModelo.h"

ConfigModelo::ConfigModelo(const Glib::ustring& label)
: tabLabel(label),
  pEntryTabLabel(NULL) {}

ConfigModelo::~ConfigModelo() {}

#include <iostream>
void ConfigModelo::desconectar() {
    if (pEntryTabLabel) {
        connectionEntryTabLabel.disconnect();
        pEntryTabLabel = NULL;
    }

    desconectarDeHijo();
}

void ConfigModelo::setEntryTabLabel(Gtk::Entry* pEntry) {
    pEntryTabLabel = pEntry;
    pEntryTabLabel->set_text(tabLabel);
    connectionEntryTabLabel = pEntryTabLabel->signal_changed().connect(
        sigc::mem_fun(*this, &ConfigModelo::on_entry_tab_label_changed));
}


Glib::ustring ConfigModelo::getTabLabel() const {
    return tabLabel;
}

Glib::ustring ConfigModelo::getTabLabelNueva() const {
    if (pEntryTabLabel)
        return pEntryTabLabel->get_text();
    else
        return tabLabel;
}

void ConfigModelo::setTabLabelNuevaComoValida() {
    tabLabel = pEntryTabLabel->get_text();
}

void ConfigModelo::on_entry_tab_label_changed() {

}
