#include "FiltradorPivoteX.h"
#include "Consulta.h"

FiltradorPivoteX::FiltradorPivoteX(const Glib::ustring& _valor)
: Filtrador("X: "), valor(_valor) {
    centradorDerecho.pack_start(valor, false, false);
}

FiltradorPivoteX::~FiltradorPivoteX() {}

void FiltradorPivoteX::filtrar(Consulta& c) {
    c.agregarXTablaP(valor.get_text());
}

