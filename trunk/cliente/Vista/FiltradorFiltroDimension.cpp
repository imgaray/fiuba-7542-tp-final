#include "FiltradorFiltroDimension.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorFiltroDimension::FiltradorFiltroDimension(const Glib::ustring& filtro,
    const Glib::ustring& _valor) : FiltradorFiltro(filtro, "") {
    if (esValido(_valor))
        setValor(_valor);
    else {
        std::string msj = "Valor inválido: ";
        msj += _valor.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }
}

FiltradorFiltroDimension::~FiltradorFiltroDimension() {}


bool FiltradorFiltroDimension::esValido(const Glib::ustring& valor) {
    return true;
}

