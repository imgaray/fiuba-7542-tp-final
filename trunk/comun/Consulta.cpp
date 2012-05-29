/*
 * Consulta.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Consulta.h"

Consulta::Consulta() : _campos(_filtros) {
	_consultaValida = true;
	_consultaDeCliente = true;
}

Consulta::~Consulta() {
}

void Consulta::definirComoConsultaAgente() {
	_consultaDeCliente = false;
}

void Consulta::definirComoConsultaCliente() {
	_consultaDeCliente = true;
}

bool Consulta::esConsultaDeCliente() const {
	return _consultaDeCliente;
}

bool Consulta::esConsultaDeAgente() const {
	return !_consultaDeCliente;
}
