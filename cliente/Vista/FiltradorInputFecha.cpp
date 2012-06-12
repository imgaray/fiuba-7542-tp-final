#include "FiltradorInputFecha.h"
#include "Consulta.h"

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

    switch (i) {
        // Año
        case 0: std::cout << "@todo FiltradorInputFecha::validar(...) por Año" << std::endl; break;
        // Mes
        case 1: std::cout << "@todo FiltradorInputFecha::validar(...) por Mes" << std::endl; break;
        // Bimestre
        case 2: std::cout << "@todo FiltradorInputFecha::validar(...) por Bimestre" << std::endl; break;
        // Trimestre
        case 3: std::cout << "@todo FiltradorInputFecha::validar(...) por Trimestre" << std::endl; break;
        // Cuatrimestre
        case 4: std::cout << "@todo FiltradorInputFecha::validar(...) por Cuatrimestre" << std::endl; break;
        // Semestre
        case 5: std::cout << "@todo FiltradorInputFecha::validar(...) por Semestre" << std::endl; break;
        // Semana del año
        case 6: std::cout << "@todo FiltradorInputFecha::validar(...) por Semana del año" << std::endl; break;
        // Día
        case 7: std::cout << "@todo FiltradorInputFecha::filtrar(...) por Día" << std::endl; break;
        default: std::cout << "FiltradorInputFecha::filtrar(...) se rompió algo, debugueá" << std::endl; break;
    }
    return f_validada;
}

Consulta& FiltradorInputFecha::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), f);
    return c;
}

Glib::ustring FiltradorInputFecha::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring FiltradorInputFecha::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}
