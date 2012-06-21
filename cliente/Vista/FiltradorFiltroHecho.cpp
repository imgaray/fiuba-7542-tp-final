#include "FiltradorFiltroHecho.h"
#include "FiltradorInputHecho.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorFiltroHecho::FiltradorFiltroHecho(const Glib::ustring& hecho,
    const Glib::ustring& _valorCombo, const std::string& _valorEntrada)
    : FiltradorFiltro(hecho, STR_NULA),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada)  {
    i =  FiltradorInputHecho::perteneceAlCombobox(valorCombo);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    valorHecho = FiltradorInputHecho::validar(i, valorEntrada);
    if (valorHecho == STR_NULA) {
        std::string msj = "Valor de entrada inválido: ";
        msj += valorEntrada.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    Glib::ustring label = valorCombo;
    label += " ";
    label += valorEntrada;
    setValor(label);
}

FiltradorFiltroHecho::~FiltradorFiltroHecho() {}

void FiltradorFiltroHecho::filtrar(Consulta& c) {
    c.agregarFiltro(getFiltro(), valorHecho);
    return c;
}

