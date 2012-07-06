#include "InputConfigModelo.h"
#include "FiltradoresTab.h"
#include "FiltradoresPanel.h"

InputConfigModelo::InputConfigModelo(unsigned _ID)
: FiltradorSoloDimensionConfigModelo(_ID) {}

InputConfigModelo::~InputConfigModelo() {}

void InputConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    filtTab->agregarEntrada(campoSelecc);
}

void InputConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarEntrada(campoSelecc);
}
