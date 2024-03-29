#include "FiltradorFiltro.h"

FiltradorFiltro::FiltradorFiltro(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : Filtrador(filtro), valor(_valor) {

    centradorDerecho.pack_start(sep, false, false);
    centradorDerecho.pack_start(valor, false, false);
}

FiltradorFiltro::~FiltradorFiltro() {}

void FiltradorFiltro::setValor(const Glib::ustring& _valor) {
    valor.set_text(_valor);
}

Glib::ustring FiltradorFiltro::getValor() {
    return valor.get_text();
}
