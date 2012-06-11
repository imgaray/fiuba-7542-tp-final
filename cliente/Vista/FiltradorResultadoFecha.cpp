#include "FiltradorResultadoFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

FiltradorResultadoFecha::FiltradorResultadoFecha(const Glib::ustring& fecha,
    const Glib::ustring& _valorCombo, const Glib::ustring& _valorEntrada)
    : FiltradorResultado(""),
    valorCombo(_valorCombo), valorEntrada(_valorEntrada)  {
    if (!FiltradorInputFecha::perteneceAlCombobox(valorCombo)) {
        std::string msj = "No pertenece al conjunto de valores posibles: ";
        msj += valorCombo.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }

    if (!FiltradorInputFecha::esValido(valorEntrada)) {
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
