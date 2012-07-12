/*
 * Tabla.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "Tabla.h"
#include "FiltradoresPanel.h"

Tabla::Tabla(FiltradoresPanel* filtradores) : Consultante(filtradores) {
    filtradores->signal_navegabilidad().connect(sigc::mem_fun(
	*this, &Consultante::on_navegabilidad_seleccionada));
	_colModelo = NULL;
	setSpinner(&s);
    s.set_no_show_all();
}

Tabla::~Tabla() {
	if (_colModelo != NULL)
		delete _colModelo;
}
