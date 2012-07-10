#include "ResultadoConfigModelo.h"
#include "Organizacion.h"
#include "FiltradorHelper.h"
#include "ExcepcionTabSoloAdmiteInputs.h"
#include "FiltradoresPanel.h"

ResultadoConfigModelo::ResultadoConfigModelo(unsigned _ID,
    const std::list< std::string >& _camposDisponibles)
: FiltradorConfigModelo(_ID, _camposDisponibles) {}

ResultadoConfigModelo::~ResultadoConfigModelo() {}

void ResultadoConfigModelo::setFiltradorEn(FiltradoresTab* filtTab) {
    throw ExcepcionTabSoloAdmiteInputs("resultado");
}

void ResultadoConfigModelo::setFiltradorEn(FiltradoresPanel* filtPanel) {
    if (Organizacion::esHecho(campoSelecc))
        filtPanel->agregarResultado(campoSelecc, _campoAux);
    else
        filtPanel->agregarResultado(campoSelecc);
}

void ResultadoConfigModelo::especializarVista() {
    entryExtra->hide();
//    entryExtra->signal_changed().connect(sigc::mem_fun(*this,
//        &FiltroConfigModelo::on_entry_changed));
}

void ResultadoConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;
    FiltradorHelper::getInstancia().popularComboAgregaciones(comboHecho);
    conectarComboHecho();

    comboHecho->set_active(0);
}

void ResultadoConfigModelo::on_combo_dimension_changed() {
    campoSeleccNuevo = comboDimension->get_active_text();
    signal_campo_changed().emit(campoSelecc, campoSeleccNuevo);
    campoSelecc = campoSeleccNuevo;

    if (Organizacion::esDimensionEspecial(campoSelecc)) {
        //comboFecha->show();
        //entryExtra->show();
        //comboHecho->hide();
        //_campoAux = comboFecha->get_active_text();
        //_valorCampo = entryExtra->get_text();
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

void ResultadoConfigModelo::completarAtributos() {
	if (Organizacion::esHecho(campoSeleccNuevo)) {
		comboHecho->set_active_text(_campoAux);
	}
	else if (Organizacion::esDimensionEspecial(campoSelecc)) {
		comboFecha->set_active_text(_campoAux);
		entryExtra->set_text(_valorCampo);
	}

	comboDimension->set_active_text(campoSeleccNuevo);
}
