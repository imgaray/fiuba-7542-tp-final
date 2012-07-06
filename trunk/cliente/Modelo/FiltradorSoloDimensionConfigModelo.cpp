#include "FiltradorSoloDimensionConfigModelo.h"

FiltradorSoloDimensionConfigModelo::FiltradorSoloDimensionConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

FiltradorSoloDimensionConfigModelo::~FiltradorSoloDimensionConfigModelo() {}

void FiltradorSoloDimensionConfigModelo::especializarVista() {
    entryExtra->hide();
    comboFecha->hide();
    comboHecho->hide();
}

void FiltradorSoloDimensionConfigModelo::on_combo_dimension_changed() {
    campoSelecc = comboDimension->get_active_text();
}

void FiltradorSoloDimensionConfigModelo::completarAtributos() {
	comboDimension->set_active_text(campoSelecc);
}
