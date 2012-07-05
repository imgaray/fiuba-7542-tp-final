#include "FiltroConfigModelo.h"
#include "Organizacion.h"

FiltroConfigModelo::FiltroConfigModelo(unsigned _ID)
: FiltradorConfigModelo(_ID) {}

FiltroConfigModelo::~FiltroConfigModelo() {}

void FiltroConfigModelo::especializarVista() {
    entryExtra->show();
    entryExtra->signal_changed().connect(sigc::mem_fun(*this,
        &FiltroConfigModelo::on_entry_changed));
}

void FiltroConfigModelo::on_combo_dimension_changed() {
    campoSelecc = comboDimension->get_active_text();

    if (Organizacion::esDimensionEspecial(campoSelecc)) {
        comboFecha->show();
        comboHecho->hide();
    } else if (Organizacion::esHecho(campoSelecc)) {
        comboFecha->hide();
        comboHecho->show();
    } else {
        comboFecha->hide();
        comboHecho->hide();
    }
    entryExtra->set_text(entryPorCampo[campoSelecc]);
}

void FiltroConfigModelo::on_entry_changed() {
    entryPorCampo[campoSelecc] = entryExtra->get_text();
}

void FiltroConfigModelo::deserializar(const NodoXml& nodo) {
	FiltradorConfigModelo::deserializar(nodo);
	entryPorCampo[campoSelecc] = _valorCampo;

	if (Organizacion::esDimensionEspecial(campoSelecc)) {
		comboFecha->set_active_text(_campoAux);
	}
	else {
		comboHecho->set_active_text(_campoAux);
	}

	comboDimension->set_active_text(campoSelecc);
}
