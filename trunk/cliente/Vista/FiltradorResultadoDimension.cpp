#include "FiltradorResultadoDimension.h"
#include "Consulta.h"

FiltradorResultadoDimension::FiltradorResultadoDimension(
    const Glib::ustring& _resultado) : FiltradorResultado(_resultado) {}

FiltradorResultadoDimension::~FiltradorResultadoDimension() {}

Consulta& FiltradorResultadoDimension::filtrar(Consulta& c) {
    c.agregarResultado(getResultado());
    return c;
}

Glib::ustring FiltradorResultadoDimension::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring FiltradorResultadoDimension::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}
