#include "FiltradorSoloDimensionConfigModelo.h"

FiltradorSoloDimensionConfigModelo::FiltradorSoloDimensionConfigModelo() {}

FiltradorSoloDimensionConfigModelo::~FiltradorSoloDimensionConfigModelo() {}

void FiltradorSoloDimensionConfigModelo::especializarVista() {
    entryExtra->hide();
    comboFecha->hide();
    comboHecho->hide();
}

void FiltradorSoloDimensionConfigModelo::on_combo_dimension_changed() {}
