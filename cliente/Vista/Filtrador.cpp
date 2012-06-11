#include "Filtrador.h"
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinner.h>
#include <gtkmm/separator.h>

Filtrador::Filtrador(const Glib::ustring& _filtro) : filtro(_filtro) {
    centradorIzquierdo.pack_end(filtro, false, false);
    pack_start(centradorIzquierdo, true, true);
    pack_start(centradorDerecho, true, true);
}

Filtrador::~Filtrador() {}
