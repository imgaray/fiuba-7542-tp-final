#include "ConfigModelo.h"

ConfigModelo::ConfigModelo(const Glib::ustring& label)
: label(label) {}

ConfigModelo::~ConfigModelo() {}

void ConfigModelo::desconectar() {
    desconectarDeHijo();
}

Glib::ustring ConfigModelo::getLabel() const {
    return label;
}

void ConfigModelo::setLabel(const Glib::ustring& _label) {
    label = _label;
}
