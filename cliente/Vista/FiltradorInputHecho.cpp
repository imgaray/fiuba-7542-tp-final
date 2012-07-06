#include "FiltradorInputHecho.h"
#include "Consulta.h"
#include "Tab.h"
#include "FiltradorHelper.h"

#define MSJ_ERROR "Sólo números"

FiltradorInputHecho::FiltradorInputHecho(const Glib::ustring& input)
: FiltradorInput(input) {
    FiltradorHelper::getInstancia().popularComboHechoInput(&valores);
    i = 0;
    valores.set_active(i);

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
            tabPadre->informarInputNoDisponible();
        }
    } else {
        if (!valido) {
            valido = true;
            tabPadre->informarInputDisponible();
        }
    }
}

void FiltradorInputHecho::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valorHecho);
}

void FiltradorInputHecho::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {

}
