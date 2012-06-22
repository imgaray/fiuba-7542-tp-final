/*
 * Tabla.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "Tabla.h"
#include <iostream>

Tabla::Tabla(FiltradoresPanel& filtradores) : ExhibidorRespuesta(filtradores) {
	_colModelo = NULL;

}

Tabla::~Tabla() {
	if (_colModelo != NULL)
		delete _colModelo;
}
