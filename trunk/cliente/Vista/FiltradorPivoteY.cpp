#include "FiltradorPivoteY.h"
#include "Consulta.h"

FiltradorPivoteY::FiltradorPivoteY(const Glib::ustring& _valor)
: Filtrador("Y: "), valor(_valor) {
    centradorDerecho.pack_start(valor, false, false);
}

FiltradorPivoteY::~FiltradorPivoteY() {}

void FiltradorPivoteY::filtrar(Consulta& c) {
    c.agregarYTablaP(valor.get_text());
}


