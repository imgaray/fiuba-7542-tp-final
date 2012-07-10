/*
 * Tabla.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "Tabla.h"

Tabla::Tabla(FiltradoresPanel* filtradores) : Consultante(filtradores) {
	_colModelo = NULL;
	setSpinner(&s);
    s.set_no_show_all();
}

Tabla::~Tabla() {
	if (_colModelo != NULL)
		delete _colModelo;
}
