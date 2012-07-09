#include "FiltradorSoloDimensionConfigModelo.h"

FiltradorSoloDimensionConfigModelo::FiltradorSoloDimensionConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorConfigModelo(_ID, _camposDisponibles) {}

FiltradorSoloDimensionConfigModelo::~FiltradorSoloDimensionConfigModelo() {}

void FiltradorSoloDimensionConfigModelo::especializarVista() {
    entryExtra->hide();
    comboFecha->hide();
    comboHecho->hide();
}

void FiltradorSoloDimensionConfigModelo::on_combo_dimension_changed() {
    campoSeleccNuevo = comboDimension->get_active_text();
    signal_campo_changed().emit(campoSelecc, campoSeleccNuevo);
    campoSelecc = campoSeleccNuevo;
}

void FiltradorSoloDimensionConfigModelo::completarAtributos() {
	comboDimension->set_active_text(campoSeleccNuevo);
}
