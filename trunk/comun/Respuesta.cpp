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
std::string Respuesta::mensajeError = "Error";
std::string Respuesta::respuestaVacia = "La Respuesta esta vacia";
std::string Respuesta::respuestaValida = "Respuesta Valida";


#define sep_fila 		sep_valor
#define sep_datoFila 	sep_datos
#define sep_principal	sep_tipo

Respuesta::Respuesta() {
	_columnas = 0;
}

Respuesta::Respuesta(const Respuesta& original) {
	this->_datos = original._datos;
	this->_columnas = original._columnas;
	this->_filaActual = original._filaActual;
}

Respuesta::Respuesta(const std::string& mensaje) {
	_msjInterno = mensaje;
	_columnas = 0;
}

Respuesta::~Respuesta() {
}

void Respuesta::operator =(const Respuesta& resp) {
	this->_datos = resp._datos;
	this->_columnas = resp._columnas;
	this->_filaActual = resp._filaActual;
}

const std::string& Respuesta::mensajeInterno() const {
	return _msjInterno;
}

std::string Respuesta::serializar() const {
	std::string datos;
	DatosDeRespuesta::const_iterator it;

	datos = _msjInterno;
	datos += sep_principal;

	for (it = _datos.begin() ; it != _datos.end() ; ) {
		const Fila f_fila = *it;
		this->cargarFila(f_fila, datos);
		++it;
		if (it !=_datos.end())
			datos += sep_fila;

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
	for (it = fila.begin() ; it != fila.end() ; ) {
		datos += *it;
		++it;
		if (it != fila.end())
			datos += sep_datoFila;
	}
}

void Respuesta::deserializar(const std::string& datos) {
	_datos.clear();
	_filaActual.clear();

	_msjInterno = u.separar(datos, sep_principal, 0);

	std::string datosSerializados = u.separar(datos, sep_principal, 1);

	u.borrarCaracter(datosSerializados, sep_fin);
	//datosSerializados.resize(datos.size() - 1);


	bool hayMasFilas = true;
	std::string fila;
	unsigned int ind = 0;
	while (hayMasFilas) {
		fila = u.separar(datosSerializados, sep_fila, ind);
		ind++;
		if (fila.empty() == false) {
			guardarFila(fila);
		}
		else {
			hayMasFilas = false;
		}
	}

	if (_datos.size() >= 1) {
		_columnas = _datos[0].size();
	}
}

void Respuesta::guardarFila(const std::string& fila) {
	Fila f_fila;
	bool hayDatos = true;
	Campo campo;
	unsigned int ind = 0;
	int camposAgregados = 0;
	while (hayDatos) {
		campo = u.separar(fila, sep_datoFila, ind);
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

	if (_filaActual.size() != _columnas)
		_columnas = _filaActual.size();

	_filaActual.clear();
}

void Respuesta::definirColumnas(size_t columnas) {
	_filaActual.reserve(columnas);
	_columnas = columnas;
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

void Respuesta::mensajeInterno(const std::string& mensaje) {
	_msjInterno = mensaje;
}

bool Respuesta::huboError() const {
	return (_msjInterno == Respuesta::mensajeError);
}
