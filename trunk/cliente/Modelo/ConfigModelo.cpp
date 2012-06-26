#include "ConfigModelo.h"

ConfigModelo::ConfigModelo(const Glib::ustring& label)
: label(label),
  pEntryLabel(NULL) {}

ConfigModelo::~ConfigModelo() {}

#include <iostream>
void ConfigModelo::desconectar() {
    if (pEntryLabel) {
        connectionEntryLabel.disconnect();
        pEntryLabel = NULL;
    }

    desconectarDeHijo();
}

void ConfigModelo::setEntryLabel(Gtk::Entry* pEntry) {
    pEntryLabel = pEntry;
    pEntryLabel->set_text(label);
    connectionEntryLabel = pEntryLabel->signal_changed().connect(
        sigc::mem_fun(*this, &ConfigModelo::on_entry_label_changed));
}


Glib::ustring ConfigModelo::getLabel() const {
    return label;
}

Glib::ustring ConfigModelo::getLabelNueva() const {
    if (pEntryLabel)
        return pEntryLabel->get_text();
    else
        return label;
}

void ConfigModelo::setLabelNuevaComoValida() {
    label = pEntryLabel->get_text();
}

void ConfigModelo::on_entry_label_changed() {

}
