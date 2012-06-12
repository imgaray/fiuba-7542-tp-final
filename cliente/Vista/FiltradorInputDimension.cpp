#include "FiltradorInputDimension.h"
#include "Respuesta.h"
#include "Consulta.h"
#include <iostream>

FiltradorInputDimension::FiltradorInputDimension(const Glib::ustring& input,
    PadreDeConsultantes* padre) : FiltradorInput(input) {
    padre->agregarConsultante(this);
    setSpinner(&s);
    centradorDerecho.pack_start(s, false, false);
    s.hide();

    // para popular el combobox
    consulta.agregarResultado(getFiltro());
}

FiltradorInputDimension::~FiltradorInputDimension() {}

void FiltradorInputDimension::procesarRespuesta(const Respuesta& rta) {
    if (rta.cantidadColumnas() != 1)
        return;

    for (unsigned i = 0; i < rta.cantidadFilas(); ++i)
        valores.append_text(rta.dato(i, 0));

    valores.set_active(0);
}

Consulta& FiltradorInputDimension::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valores.get_active_text());
    return c;
}

Glib::ustring FiltradorInputDimension::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring FiltradorInputDimension::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}
