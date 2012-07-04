#include "FiltroConfigModelo.h"
#include "Organizacion.h"

FiltroConfigModelo::FiltroConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

FiltroConfigModelo::~FiltroConfigModelo() {}

void FiltroConfigModelo::especializarVista() {
    entryExtra->show();
}

void FiltroConfigModelo::on_combo_dimension_changed() {
    Glib::ustring combo = comboDimension->get_active_text();

    if (Organizacion::esDimensionEspecial(combo)) {
        comboFecha->show();
        comboHecho->hide();
    } else if (Organizacion::esHecho(combo)) {
        comboFecha->hide();
        comboHecho->show();
    } else {
        comboFecha->hide();
        comboHecho->hide();
    }
}

