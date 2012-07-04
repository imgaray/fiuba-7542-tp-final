#include "ResultadoConfigModelo.h"
#include "Organizacion.h"

ResultadoConfigModelo::ResultadoConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

ResultadoConfigModelo::~ResultadoConfigModelo() {}

void ResultadoConfigModelo::especializarVista() {
    entryExtra->hide();
}

void ResultadoConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;
    comboHecho->clear_items();
    comboHecho->append_text("Soy el combo de hechos con agregaciones");

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
        comboHecho->show();
    } else {
        comboFecha->hide();
        comboHecho->hide();
    }
}
