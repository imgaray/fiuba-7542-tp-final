#include "ResultadoConfigModelo.h"
#include "Organizacion.h"
#include "FiltradorHelper.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

ResultadoConfigModelo::ResultadoConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

ResultadoConfigModelo::~ResultadoConfigModelo() {}

void ResultadoConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("resultado");
}

void ResultadoConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    if (Organizacion::esHecho(campoSelecc))
        filtPanel->agregarResultado(campoSelecc, _campoAux);
    else if (Organizacion::esDimensionEspecial(campoSelecc))
        filtPanel->agregarResultado(campoSelecc, _campoAux, _valorCampo);
    else
        filtPanel->agregarResultado(campoSelecc);
}

void ResultadoConfigModelo::especializarVista() {
    entryExtra->hide();
}

void ResultadoConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;
    FiltradorHelper::getInstancia().popularComboAgregaciones(comboHecho);

    comboHecho->set_active(0);
}

void ResultadoConfigModelo::on_combo_dimension_changed() {
    campoSelecc = comboDimension->get_active_text();

    if (Organizacion::esDimensionEspecial(campoSelecc)) {
        comboFecha->show();
        entryExtra->show();
        comboHecho->hide();
        _campoAux = comboFecha->get_active_text();
    } else if (Organizacion::esHecho(campoSelecc)) {
        comboFecha->hide();
        entryExtra->hide();
        comboHecho->show();
        _campoAux = comboHecho->get_active_text();
    } else {
        comboFecha->hide();
        entryExtra->hide();
        comboHecho->hide();
    }
}
