#include "PanelConfigModelo.h"

PanelConfigModelo::PanelConfigModelo()
: ConfigModelo(NOMBRE_PANEL_POR_DEFECTO) {

}

PanelConfigModelo::~PanelConfigModelo() {
    desconectar();
}

void PanelConfigModelo::desconectarDeHijo() {

}
