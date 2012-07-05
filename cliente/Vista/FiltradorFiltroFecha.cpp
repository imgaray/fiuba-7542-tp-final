#include "FiltradorFiltroFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"
#include "FiltradorHelper.h"

FiltradorFiltroFecha::FiltradorFiltroFecha(const Glib::ustring& fecha,
    const Glib::ustring& _valorCombo, const std::string& _valorEntrada)
    : FiltradorFiltro(fecha, STR_NULA),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada) {
    const FiltradorHelper& helper = FiltradorHelper::getInstancia();
    i = helper.perteneceAlComboFecha(valorCombo);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    f = helper.validarFecha(i, valorEntrada);
    if (f == STR_NULA) {
        std::string msj = "Valor de entrada inválido: ";
        msj += valorEntrada.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    Glib::ustring label = valorCombo;
    label += " ";
    label += valorEntrada;
    setValor(label);
}

FiltradorFiltroFecha::~FiltradorFiltroFecha() {}

void FiltradorFiltroFecha::filtrar(Consulta& c) {
    c.agregarFiltro(getFiltro(), f);
}
