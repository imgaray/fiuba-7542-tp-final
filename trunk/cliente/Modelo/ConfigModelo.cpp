#include "ConfigModelo.h"

ConfigModelo::ConfigModelo(): pEntryLabel(NULL) {
}

ConfigModelo::ConfigModelo(const Glib::ustring& label)
: label(label),
  pEntryLabel(NULL) {}

ConfigModelo::~ConfigModelo() {}

void ConfigModelo::desconectar() {
    desconectar(connectionEntryLabel, pEntryLabel);

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

void ConfigModelo::setLabel(const Glib::ustring& _label) {
    label = _label;
}

void ConfigModelo::on_entry_label_changed() {

}
