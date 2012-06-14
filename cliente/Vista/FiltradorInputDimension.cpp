#include "FiltradorInputDimension.h"
#include "Respuesta.h"
#include "Consulta.h"
#include <iostream>
#include <exception>
#include <cassert>

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
    if (valores.get_active_text() != STR_NULA) {
        std::cout << "Filtrador ya tiene su combo actualizado" << std::endl;
        return;
    }
	std::cout << "FILTRADOR: cantidad columnas respuesta " << rta.cantidadColumnas() << std::endl;
    if (rta.cantidadColumnas() != 1)
        throw "*******ERROR: FiltradorInputDimension esperaba una respuesta con 1 columna";

    for (unsigned i = 0; i < rta.cantidadFilas(); ++i)
        valores.append_text(rta.dato(i, 0));

    valores.set_active(0);
}

Consulta& FiltradorInputDimension::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valores.get_active_text());
    return c;
}

void FiltradorInputDimension::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    std::cout << this << " recibiendo navegación ( " << input << ", " << valor << ")" << std::endl;
    if (input == getFiltro())
        valores.set_active_text(valor);
}

