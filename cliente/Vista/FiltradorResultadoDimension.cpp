#include "FiltradorResultadoDimension.h"
#include "Consulta.h"

FiltradorResultadoDimension::FiltradorResultadoDimension(
    const Glib::ustring& _resultado) : FiltradorResultado(_resultado) {}

FiltradorResultadoDimension::~FiltradorResultadoDimension() {}

Consulta& FiltradorResultadoDimension::filtrar(Consulta& c) {
    c.agregarResultado(getResultado());
    return c;
}
