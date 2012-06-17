#include "Filtrador.h"
#include "Validador.h"

Filtrador::Filtrador(char _tipo, const Glib::ustring& _nombre)
: etiqueta(_nombre), nombre (_nombre) {
    tipo = _tipo;
    centradorIzquierdo.pack_end(etiqueta, false, false);
    pack_start(centradorIzquierdo, true, true);
    pack_start(centradorDerecho, true, true);
}

Filtrador::Filtrador(char _tipo,
                     const Glib::ustring& _etiqueta,
                     const Glib::ustring& _nombre)
: etiqueta(_etiqueta), nombre(_nombre) {
    tipo = _tipo;
    centradorIzquierdo.pack_end(etiqueta, false, false);
    pack_start(centradorIzquierdo, true, true);
    pack_start(centradorDerecho, true, true);
}

