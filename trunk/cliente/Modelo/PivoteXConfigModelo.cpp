#include "PivoteXConfigModelo.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

PivoteXConfigModelo::PivoteXConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorSoloDimensionConfigModelo(_ID, _camposDisponibles) {}

PivoteXConfigModelo::~PivoteXConfigModelo() {}

void PivoteXConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("pivote x");
}

void PivoteXConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarXTablaP(campoSelecc);
}

