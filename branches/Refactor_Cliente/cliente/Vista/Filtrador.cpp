#include "Filtrador.h"

Filtrador::Filtrador(const Glib::ustring& _filtro) : filtro(_filtro) {
    centradorIzquierdo.pack_end(filtro, false, false);
    pack_start(centradorIzquierdo, true, true);
    pack_start(centradorDerecho, true, true);
}

Filtrador::~Filtrador() {}

Glib::ustring Filtrador::getFiltro() {
    return filtro.get_text();
}
