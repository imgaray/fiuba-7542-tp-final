#include "FiltradorInputFecha.h"
#include "Consulta.h"
#include "Tab.h"
#include "FiltradorHelper.h"

#define MSJ_ERROR "Fecha inválida"

FiltradorInputFecha::FiltradorInputFecha(const Glib::ustring& input)
: FiltradorInput(input) {
    FiltradorHelper::getInstancia().popularComboFecha(&valores);
    i = 0;
    valores.set_active(i);

    centradorDerecho.pack_end(entrada, false, false);

    valores.signal_changed().connect(sigc::mem_fun(*this,
            &FiltradorInputFecha::on_combo_changed));

    entrada.signal_activate().connect(sigc::mem_fun(*this,
            &FiltradorInputFecha::on_entry_activated));
}

FiltradorInputFecha::~FiltradorInputFecha() {}

void FiltradorInputFecha::on_combo_changed() {
    i = valores.get_active_row_number();
}

void FiltradorInputFecha::on_entry_activated() {
    f = FiltradorHelper::getInstancia().validarFecha(i, entrada.get_text());
    if (f == STR_NULA) {
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

void FiltradorInputFecha::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), f);
}

void FiltradorInputFecha::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    if (input == getFiltro()) {
        valores.set_active_text(FiltradorHelper::getInstancia().
            getValorComboFechaParaNavegacion());
        entrada.set_text(valor);
        signal_navegabilidad_seleccionada.emit();
    }
}
