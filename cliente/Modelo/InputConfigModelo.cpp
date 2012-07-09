#include "InputConfigModelo.h"
#include "FiltradoresTab.h"
#include "FiltradoresPanel.h"

InputConfigModelo::InputConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorSoloDimensionConfigModelo(_ID,  _camposDisponibles) {}

InputConfigModelo::~InputConfigModelo() {}

void InputConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    filtTab->agregarEntrada(campoSelecc);
}

void InputConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarEntrada(campoSelecc);
}
