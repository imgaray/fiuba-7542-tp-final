#include "Hecho.h"

Hecho::Hecho(const Hecho& original) {
    etiqueta = original.etiqueta;
    valor = original.valor;
}

Hecho::Hecho(const Glib::ustring& _etiqueta, double _valor) {
    etiqueta = _etiqueta;
    valor = _valor;
}

Hecho::~Hecho() {}

const Glib::ustring& Hecho::getEtiqueta() const {
    return etiqueta;
}

double Hecho::getValor() const {
    return valor;
}
