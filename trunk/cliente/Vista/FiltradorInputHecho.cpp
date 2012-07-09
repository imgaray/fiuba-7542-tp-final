#include "FiltradorInputHecho.h"
#include "Consulta.h"
#include "Tab.h"
#include "FiltradorHelper.h"

#define MSJ_ERROR "Sólo números"
#define ENTRY_DEF_VALUE "0"

FiltradorInputHecho::FiltradorInputHecho(const Glib::ustring& input)
: FiltradorInput(input) {
    FiltradorHelper::getInstancia().popularComboHechoInput(&valores);
    i = 0;
    valores.set_active(i);
    entrada.set_text(ENTRY_DEF_VALUE);

    centradorDerecho.pack_start(entrada, false, false);

    valores.signal_changed().connect(sigc::mem_fun(*this,
        &FiltradorInputHecho::on_combo_changed));
    entrada.signal_activate().connect(sigc::mem_fun(*this,
        &FiltradorInputHecho::on_entry_activated));
}

FiltradorInputHecho::~FiltradorInputHecho() {}

void FiltradorInputHecho::on_combo_changed() {
    i = valores.get_active_row_number();
}

void FiltradorInputHecho::on_entry_activated() {
    valorHecho = FiltradorHelper::getInstancia().validarHecho(
        i, entrada.get_text());

    if (valorHecho == STR_NULA) {
        entrada.set_text(MSJ_ERROR);
        if (valido) {
            valido = false;
            _signal_input_disponible.emit(valido);
        }
    } else {
        if (!valido) {
            valido = true;
            _signal_input_disponible.emit(valido);
        }
    }
}

void FiltradorInputHecho::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valorHecho);
}

void FiltradorInputHecho::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {

}
