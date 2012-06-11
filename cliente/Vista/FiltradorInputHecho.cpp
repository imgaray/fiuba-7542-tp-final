#include "FiltradorInputHecho.h"

#define CANT_COMBO 2
Glib::ustring FiltradorInputHecho::valoresCombo[CANT_COMBO] = { ">", "<" };

FiltradorInputHecho::FiltradorInputHecho(const Glib::ustring& input)
: FiltradorInput(input) {
    for (unsigned i = 0; i < CANT_COMBO; ++i)
        valores.append_text(valoresCombo[i]);

    centradorDerecho.pack_end(entrada, false, false);
}

FiltradorInputHecho::~FiltradorInputHecho() {}

bool FiltradorInputHecho::perteneceAlCombobox(const Glib::ustring& valor) {
    bool pertenece = false;
    unsigned i = 0;
    while (!pertenece && i < CANT_COMBO)
        pertenece = valor == valoresCombo[i++];

    return pertenece;
}

bool FiltradorInputHecho::esValido(const Glib::ustring& valor) {
    return true;
}
