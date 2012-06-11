#include "FiltradorFiltroHecho.h"
#include "FiltradorInputHecho.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorFiltroHecho::FiltradorFiltroHecho(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : FiltradorFiltro(filtro, "") {
    if (esValido(_valor))
        setValor(_valor);
    else {
        std::string msj = "Valor inválido: ";
        msj += _valor.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }
}

FiltradorFiltroHecho::~FiltradorFiltroHecho() {}


bool FiltradorFiltroHecho::esValido(const Glib::ustring& valor) {
    return FiltradorInputHecho::perteneceAlCombobox(valor);
}

