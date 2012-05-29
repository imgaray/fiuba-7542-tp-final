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

Consulta::Consulta(const Consulta& original) {
	this->_campos = original._campos;
	this->_consultaDeCliente = original._consultaDeCliente;
	this->_consultaValida = original._consultaValida;
	this->_entradas = original._entradas;
	this->_resultados = original._resultados;
	this->_filtros = original._filtros;
}

Consulta::~Consulta() {
}


std::string Consulta::serializar() {
	return "Serializado";

}

void Consulta::deserializar(const std::string& consulta) {

}

void Consulta::agregarFiltro(const std::string filtro,
			const std::string valor) {
	if (filtro.empty() == false && valor.empty() == false) {
		this->_filtros[filtro] = valor;
	}
}

void Consulta::agregarEntrada(const std::string entrada,
				const std::string valor) {
	if (entrada.empty() == false && valor.empty() == false) {
			this->_entradas[entrada] = valor;
		}
}

void Consulta::agregarResultado(const std::string resultado) {
	if (resultado.empty() == false) {
		this->_resultados.push_back(resultado);
	}
}



const std::string& Consulta::

void Consulta::definirComoConsultaAgente() {
	this->_consultaDeCliente = false;
}

void Consulta::definirComoConsultaCliente() {
	this->_consultaDeCliente = true;
}

int Consulta::cantidadResultados() {
	return 2;
}

int Consulta::cantidadFiltros() {
	return 1;
}

int Consulta::cantidadEntradas() {
	return 1;
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
