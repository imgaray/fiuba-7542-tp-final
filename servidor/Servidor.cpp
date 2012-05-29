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

Respuesta resolver(Consulta& consulta) {
	Respuesta ret;
	if (verificador->verificarConsulta(consulta)) {
		ret = bdd->resolverConsulta(consulta);
	}
	return ret;
}

void Servidor::comenzar() {
	intermediario.start();
}

void Servidor::detener() {
	// TODO(Nacho): detener el servidor
	intermediario.detener();
}

void Servidor::persistir() {
	// TODO(Nacho): iniciar la persistencia
	bdd.persistir();
}

Servidor::Servidor() {
	// TODO Auto-generated constructor stub
}

Servidor::~Servidor() {
	// TODO Auto-generated destructor stub
}
