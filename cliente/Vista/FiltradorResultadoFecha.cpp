#include "FiltradorResultadoFecha.h"
#include "FiltradorInputFecha.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorResultadoFecha::FiltradorResultadoFecha(const Glib::ustring& fecha,
    const Glib::ustring& valorCombo, const Glib::ustring& valorEntrada)
    : FiltradorResultado("") {
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

    label = fecha;
    label += " ";
    label += valorCombo;
    label += " ";
    label += valorEntrada;
    setResultado(label);
}

FiltradorResultadoFecha::~FiltradorResultadoFecha() {}

