#include "ResultadoConfigModelo.h"
#include "Organizacion.h"
#include "FiltradorHelper.h"

ResultadoConfigModelo::ResultadoConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

ResultadoConfigModelo::~ResultadoConfigModelo() {}

void ResultadoConfigModelo::especializarVista() {
    entryExtra->hide();
}

void ResultadoConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;
    FiltradorHelper::getInstancia().popularComboAgregaciones(comboHecho);

    comboHecho->set_active(0);
}

void ResultadoConfigModelo::on_combo_dimension_changed() {
    Glib::ustring combo = comboDimension->get_active_text();

    if (Organizacion::esDimensionEspecial(combo)) {
        comboFecha->show();
        entryExtra->show();
        comboHecho->hide();
    } else if (Organizacion::esHecho(combo)) {
        comboFecha->hide();
        entryExtra->hide();
        comboHecho->show();
    } else {
        comboFecha->hide();
        entryExtra->hide();
        comboHecho->hide();
    }
}
