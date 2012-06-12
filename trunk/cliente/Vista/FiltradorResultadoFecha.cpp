#include "FiltradorResultadoFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorResultadoFecha::FiltradorResultadoFecha(const Glib::ustring& fecha,
    const Glib::ustring& _valorCombo, const Glib::ustring& _valorEntrada)
    : FiltradorResultado(STR_NULA),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada)  {
    i = FiltradorInputFecha::perteneceAlCombobox(valorCombo);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    f = FiltradorInputFecha::validar(i, valorEntrada);
    if (f == STR_NULA) {
        std::string msj = "Valor de entrada inválido: ";
        msj += valorEntrada.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    Glib::ustring label = valorCombo;
    label += " ";
    label += valorEntrada;
    setResultado(label);
}

FiltradorResultadoFecha::~FiltradorResultadoFecha() {}

Consulta& FiltradorResultadoFecha::filtrar(Consulta& c) {
    std::cout << "@todo Consulta& FiltradorResultadoFecha::filtrar(Consulta& c)" << std::endl;
    return c;
}

Glib::ustring FiltradorResultadoFecha::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring  FiltradorResultadoFecha::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}
