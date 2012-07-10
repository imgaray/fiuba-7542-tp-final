#include "FiltradorInputDimension.h"
#include "Respuesta.h"
#include "Consulta.h"
#include "Tab.h"

FiltradorInputDimension::FiltradorInputDimension(const Glib::ustring& input)
: FiltradorInput(input) {
    setSpinner(&s);
    centradorDerecho.pack_start(s, false, false);
    s.hide();
    s.set_no_show_all();

    // para popular el combobox
    consulta.agregarResultado(getFiltro());
}

FiltradorInputDimension::~FiltradorInputDimension() {}

void FiltradorInputDimension::procesarRespuesta(const Respuesta& rta) {
    if (valores.get_active_text() != STR_NULA)
        return;

    for (unsigned i = 0; i < rta.cantidadFilas(); ++i)
        valores.append_text(rta.dato(i, 0));

    valores.set_active(0);
    padre->removerConsultante(getID());
    _signal_input_disponible.emit(true);
}

void FiltradorInputDimension::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valores.get_active_text());
}

void FiltradorInputDimension::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    if (input == getFiltro()) {
        valores.set_active_text(valor);
        signal_navegabilidad_seleccionada.emit();
    }
}

