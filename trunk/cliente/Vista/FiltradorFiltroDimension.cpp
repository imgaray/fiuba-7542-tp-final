#include "FiltradorFiltroDimension.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorFiltroDimension::FiltradorFiltroDimension(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : FiltradorFiltro(filtro, _valor) {}

FiltradorFiltroDimension::~FiltradorFiltroDimension() {}


Consulta&  FiltradorFiltroDimension::filtrar(Consulta& c) {
    c.agregarFiltro(getFiltro(), getValor());
    return c;
}

Glib::ustring FiltradorFiltroDimension::pertenece(const Glib::ustring& _valor) {
    if (getValor() == _valor)
        return getFiltro();
    else
        return STR_NULA;
}
