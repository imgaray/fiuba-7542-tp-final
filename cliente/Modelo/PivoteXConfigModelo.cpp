#include "PivoteXConfigModelo.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

PivoteXConfigModelo::PivoteXConfigModelo(unsigned _ID)
: FiltradorSoloDimensionConfigModelo(_ID) {}

PivoteXConfigModelo::~PivoteXConfigModelo() {}

void PivoteXConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("pivote x");
}

void PivoteXConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarXTablaP(campoSelecc);
}

