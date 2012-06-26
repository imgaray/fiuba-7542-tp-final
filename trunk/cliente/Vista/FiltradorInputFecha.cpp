#include "FiltradorInputFecha.h"
#include "Consulta.h"
#include "Tab.h"

#define MSJ_ERROR "Fecha inválida"
#define CANT_COMBO 8

M_Fechas FiltradorInputFecha::m_fechas;
Utilitario FiltradorInputFecha::u;

Glib::ustring FiltradorInputFecha::valoresCombo[CANT_COMBO] = {
    "Año", "Mes", "Bimestre", "Trimestre", "Cuatrimestre", "Semestre",
    "Semana del año", "Dia" };

FiltradorInputFecha::FiltradorInputFecha(const Glib::ustring& input)
: FiltradorInput(input) {
    for (unsigned j = 0; j < CANT_COMBO; ++j)
        valores.append_text(valoresCombo[j]);

    i = 0;
    valores.set_active(i);

    centradorDerecho.pack_end(entrada, false, false);

    valores.signal_changed().connect(sigc::mem_fun(*this,
            &FiltradorInputFecha::on_combo_changed));

    entrada.signal_activate().connect(sigc::mem_fun(*this,
            &FiltradorInputFecha::on_entry_activated));
}

FiltradorInputFecha::~FiltradorInputFecha() {}

int FiltradorInputFecha::perteneceAlCombobox(const Glib::ustring& valor) {
    bool pertenece = false;
    unsigned j = 0;
    while (!pertenece && j < CANT_COMBO)
        pertenece = valor == valoresCombo[j++];

    if (pertenece)
        return --j;
    else
        return NO_PERTENECE;
}

void FiltradorInputFecha::on_combo_changed() {
    i = valores.get_active_row_number();
}

void FiltradorInputFecha::on_entry_activated() {
    f = validar(i, entrada.get_text());
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


Fecha FiltradorInputFecha::validar(int i, const Glib::ustring& valor) {
    Fecha f_validada;
    Glib::ustring pri_str = u.separar(valor, '-', 0);
    Glib::ustring seg_str = u.separar(valor, '-', 1);
    Glib::ustring terc_str = u.separar(valor, '-', 2);

    int pri_int = -1;
    int seg_int = -1;
    int terc_int = -1;
    if (pri_str != STR_NULA)
        pri_int = u.convertirAEntero(pri_str);
    if (seg_str != STR_NULA)
        seg_int = u.convertirAEntero(seg_str);
    if (terc_str != STR_NULA)
        terc_int = u.convertirAEntero(terc_str);

    switch (i) {
        // Año
        case 0: f_validada = m_fechas.anio(pri_str); break;
        // Mes
        case 1: f_validada = m_fechas.mes(pri_int, seg_str); break;
        // Bimestre
        case 2: f_validada = m_fechas.bimestre(pri_int, seg_str); break;
        // Trimestre
        case 3: f_validada = m_fechas.trimestre(pri_int, seg_str); break;
        // Cuatrimestre
        case 4: f_validada = m_fechas.cuatrimestre(pri_int, seg_str); break;
        // Semestre
        case 5: f_validada = m_fechas.semestre(pri_int, seg_str); break;
        // Semana del año
        case 6: f_validada = m_fechas.semana(pri_int, seg_str); break;
        // Día
        case 7: f_validada = m_fechas.fecha(pri_int, seg_int, terc_int); break;
        default: break;
    }
    return f_validada;
}

void FiltradorInputFecha::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), f);
}

void FiltradorInputFecha::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    if (input == getFiltro()) {
        valores.set_active_text("Dia");
        entrada.set_text(valor);
        signal_navegabilidad_seleccionada.emit();
    }
}
