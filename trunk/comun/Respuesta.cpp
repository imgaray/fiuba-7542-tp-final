/*
 * Respuesta.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Respuesta.h"
#include "Utilitario.h"
#include <iostream>
Campo Respuesta::campo_nulo;

Respuesta::Respuesta() {
}

Respuesta::Respuesta(const Respuesta& original) {
	this->_datos = original._datos;
	this->_columnas = original._columnas;
	this->_filaActual = original._filaActual;
}

Respuesta::~Respuesta() {
}

void Respuesta::operator =(const Respuesta& resp) {
	this->_datos = resp._datos;
	this->_columnas = resp._columnas;
	this->_filaActual = resp._filaActual;
}

std::string Respuesta::serializar() const {
	std::string datos;
	DatosDeRespuesta::const_iterator it;
	for (it = _datos.begin() ; it != _datos.end() ; ++it) {
		const Fila f_fila = *it;
		this->cargarFila(f_fila, datos);
	}

	datos += sep_fin;

	return datos;
}


void Respuesta::limpiar() {
	_columnas = 0;
	_filaActual.clear();
	_datos.clear();
}

void Respuesta::cargarFila(const Fila& fila, std::string& datos) const {
	Fila::const_iterator it;
	for (it = fila.begin() ; it != fila.end() ; ++it) {
		datos += *it;
		datos += sep_valor;
	}
	datos += sep_tipo;
}

void Respuesta::deserializar(const std::string& datos) {
	_datos.clear();
	_filaActual.clear();
	bool hayMasFilas = true;
	std::string fila;
	unsigned int ind = 0;
	while (hayMasFilas) {
		fila = Utilitario::separar(datos, sep_tipo, ind);
		ind++;
		if (fila.empty() == false) {
			guardarFila(fila);
		}
		else {
			hayMasFilas = false;
		}
	}
}

void Respuesta::guardarFila(const std::string& fila) {
	Fila f_fila;
	bool hayDatos = true;
	Campo campo;
	unsigned int ind = 0;
	int camposAgregados = 0;
	while (hayDatos) {
		campo = Utilitario::separar(fila, sep_valor, ind);
		ind++;

		if (campo.empty() == false) {
			f_fila.push_back(campo);
			camposAgregados++;
		}
		else
			hayDatos = false;
	}
	if (camposAgregados > 0)
		_datos.push_back(f_fila);
}

void Respuesta::agregar(const std::string& dato) {
	_filaActual.push_back(dato);
}
void Respuesta::filaCompletada() {
	_datos.push_back(_filaActual);
	_filaActual.clear();
}

void Respuesta::definirColumnas(size_t columnas) {
	_filaActual.reserve(columnas);
}

const std::string& Respuesta::dato(size_t fila, size_t columna) const {
	if (_datos.size() > fila ) {
		const Fila &f_fila = _datos[fila];

		if (f_fila.size() > columna)
			return f_fila[columna];
		else
			return Respuesta::campo_nulo;
	}
	else {
		return Respuesta::campo_nulo;
	}
}

size_t Respuesta::cantidadColumnas() const {
	return _columnas;
}

size_t Respuesta::cantidadFilas() const {
	return _datos.size();
}
