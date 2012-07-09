#include "FiltradorInputFecha.h"
#include "Consulta.h"
#include "Tab.h"
#include "FiltradorHelper.h"
#include <ctime>
#include "Utilitario.h"

#define MSJ_ERROR "Fecha inválida"

FiltradorInputFecha::FiltradorInputFecha(const Glib::ustring& input)
: FiltradorInput(input), infoError(MSJ_ERROR) {
    FiltradorHelper::getInstancia().popularComboFecha(&valores);
    i = 0;
    valores.set_active(i);
    time_t t = time(0);
    tm* t_ahora = localtime(&t);
    Utilitario u;
    entrada.set_text(u.convertirAString( t_ahora->tm_year + 1900));

    centradorDerecho.pack_start(entrada, false, false);
    centradorDerecho.pack_start(infoError, false, false);
    infoError.hide();
    infoError.set_no_show_all();

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
        infoError.show();
        entrada.set_text(MSJ_ERROR);
        if (valido) {
            valido = false;
            _signal_input_disponible.emit(valido);
        }
    } else {
        infoError.hide();
        if (!valido) {
            valido = true;
            _signal_input_disponible.emit(valido);
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
