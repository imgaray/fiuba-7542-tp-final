#include "FiltradorInputHecho.h"
#include "Consulta.h"

#define MSJ_ERROR "Sólo números"
#define CANT_COMBO 2
Glib::ustring FiltradorInputHecho::valoresCombo[CANT_COMBO] = { ">", "<" };

FiltradorInputHecho::FiltradorInputHecho(const Glib::ustring& input)
: FiltradorInput(input) {
    for (unsigned j = 0; j < CANT_COMBO; ++j)
        valores.append_text(valoresCombo[j]);

    i = 0;
    valores.set_active(i);

    centradorDerecho.pack_end(entrada, false, false);
}

FiltradorInputHecho::~FiltradorInputHecho() {}

int FiltradorInputHecho::perteneceAlCombobox(const Glib::ustring& valor) {
    bool pertenece = false;
    unsigned j = 0;
    while (!pertenece && j < CANT_COMBO)
        pertenece = valor == valoresCombo[j++];

    if (pertenece)
        return --j;
    else
        return NO_PERTENECE;
}

Glib::ustring FiltradorInputHecho::validar(int i, const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring  FiltradorInputHecho::filtrar(const Glib::ustring& )" << std::endl;
    Glib::ustring val = valoresCombo[i];
    val += valor;
    return val;
}

void FiltradorInputHecho::on_combo_changed() {
    i = valores.get_active_row_number();
}

void FiltradorInputHecho::on_entry_activated() {
    valorHecho = validar(i, entrada.get_text());
    if (valorHecho == STR_NULA)
        entrada.set_text(MSJ_ERROR);
}

Consulta& FiltradorInputHecho::filtrar(Consulta& c) {
    c.agregarEntrada(getFiltro(), valorHecho);
    return c;
}

Glib::ustring FiltradorInputHecho::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring  FiltradorInputHecho::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}

