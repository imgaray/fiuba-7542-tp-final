#include "PivoteYConfigModelo.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

PivoteYConfigModelo::PivoteYConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorSoloDimensionConfigModelo(_ID, _camposDisponibles) {}

PivoteYConfigModelo::~PivoteYConfigModelo() {}

void PivoteYConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("pivote y");
}

void PivoteYConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    filtPanel->agregarYTablaP(campoSelecc);
}

