/*
 * Servidor.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Servidor.h"
#include "Definiciones.h"
#include "../comun/Socket.h"
#include <iostream>

void Servidor::comenzar() {
	// TODO(Nacho): comenzar el servidor
	intermediario.start();
}

void Servidor::detener() {
	// TODO(Nacho): detener el servidor
	intermediario.detener();
}

void Servidor::persistir() {
	// TODO(Nacho): iniciar la persistencia
}

Servidor::Servidor(unsigned short port): intermediario(port) {
	// TODO Auto-generated constructor stub
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}
