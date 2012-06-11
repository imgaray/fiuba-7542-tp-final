#include "FiltradorInputHecho.h"
#include "Consulta.h"

#define CANT_COMBO 2
Glib::ustring FiltradorInputHecho::valoresCombo[CANT_COMBO] = { ">", "<" };

FiltradorInputHecho::FiltradorInputHecho(const Glib::ustring& input)
: FiltradorInput(input) {
    for (unsigned i = 0; i < CANT_COMBO; ++i)
        valores.append_text(valoresCombo[i]);

    centradorDerecho.pack_end(entrada, false, false);
}

FiltradorInputHecho::~FiltradorInputHecho() {}

int FiltradorInputHecho::perteneceAlCombobox(const Glib::ustring& valor) {
    bool pertenece = false;
    unsigned i = 0;
    while (!pertenece && i < CANT_COMBO)
        pertenece = valor == valoresCombo[i++];

    if (pertenece)
        return --i;
    else
        return NO_PERTENECE;
}

bool FiltradorInputHecho::esValido(const Glib::ustring& valor) {
    return true;
}

Consulta& FiltradorInputHecho::filtrar(Consulta& c) {
    std::cout << "@todo Consulta& FiltradorInputHecho::filtrar(Consulta& c)" << std::endl;
    return c;
}
