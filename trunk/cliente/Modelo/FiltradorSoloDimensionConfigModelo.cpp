#include "FiltradorSoloDimensionConfigModelo.h"

FiltradorSoloDimensionConfigModelo::FiltradorSoloDimensionConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

FiltradorSoloDimensionConfigModelo::~FiltradorSoloDimensionConfigModelo() {}

void FiltradorSoloDimensionConfigModelo::especializarVista() {
    entryExtra->hide();
    comboFecha->hide();
    comboHecho->hide();
}

void FiltradorSoloDimensionConfigModelo::on_combo_dimension_changed() {}
