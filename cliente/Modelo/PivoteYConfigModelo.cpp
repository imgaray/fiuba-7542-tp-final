#include "PivoteYConfigModelo.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

PivoteYConfigModelo::PivoteYConfigModelo(unsigned _ID)
: FiltradorSoloDimensionConfigModelo(_ID) {}

PivoteYConfigModelo::~PivoteYConfigModelo() {}

void PivoteYConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("pivote y");
}

void PivoteYConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarYTablaP(campoSelecc);
}

