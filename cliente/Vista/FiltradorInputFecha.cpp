#include "FiltradorInputFecha.h"
#include "Consulta.h"
#include "Utilitario.h"
#include "M_Fechas.h"

#define MSJ_ERROR "Fecha inválida"
#define CANT_COMBO 8

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
    if (f == STR_NULA)
        entrada.set_text(MSJ_ERROR);
}


Fecha FiltradorInputFecha::validar(int i, const Glib::ustring& valor) {
    std::cout << "@todo Fecha FiltradorInputFecha::validar(int i, const Glib::ustring& valor): terminar de implementar" << std::endl;
    Fecha f_validada;
    Glib::ustring pri_str = Utilitario::separar(valor, '-', 0);
    Glib::ustring seg_str = Utilitario::separar(valor, '-', 1);
    Glib::ustring terc_str = Utilitario::separar(valor, '-', 2);

    int pri_int = -1;
    int seg_int = -1;
    int terc_int = -1;
    if (pri_str != STR_NULA)
        pri_int = Utilitario::convertirAEntero(pri_str);
    if (seg_str != STR_NULA)
        seg_int = Utilitario::convertirAEntero(seg_str);
    if (terc_str != STR_NULA)
        terc_int = Utilitario::convertirAEntero(terc_str);

    switch (i) {
        // Año
        case 0: f_validada = M_Fechas::anio(pri_str); break;
        // Mes
        case 1: f_validada = M_Fechas::mes(pri_int, seg_str); break;
        // Bimestre
        case 2: f_validada = M_Fechas::bimestre(pri_int, seg_str); break;
        // Trimestre
        case 3: f_validada = M_Fechas::trimestre(pri_int, seg_str); break;
        // Cuatrimestre
        case 4: f_validada = M_Fechas::cuatrimestre(pri_int, seg_str); break;
        // Semestre
        case 5: f_validada = M_Fechas::semestre(pri_int, seg_str); break;
        // Semana del año
        case 6: std::cout << "@todo FiltradorInputFecha::validar(...) por Semana del año" << std::endl; break;
        // Día
        case 7: f_validada = M_Fechas::fecha(pri_int, seg_int, terc_int); break;
        default: std::cout << "FiltradorInputFecha::filtrar(...) se rompió algo, debugueá" << std::endl; break;
    }
    return f_validada;
}

Consulta& FiltradorInputFecha::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), f);
    return c;
}
