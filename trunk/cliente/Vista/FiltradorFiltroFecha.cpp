#include "FiltradorFiltroFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorFiltroFecha::FiltradorFiltroFecha(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : FiltradorFiltro(filtro, "") {
    if (esValido(_valor))
        setValor(_valor);
    else {
        std::string msj = "Valor inválido: ";
        msj += _valor.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }
}

FiltradorFiltroFecha::~FiltradorFiltroFecha() {}


bool FiltradorFiltroFecha::esValido(const Glib::ustring& valor) {
    return FiltradorInputFecha::perteneceAlCombobox(valor);
}
