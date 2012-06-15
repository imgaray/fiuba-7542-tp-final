/*
 * Organizacion.cpp
 *
 *  Created on: 03/06/2012
 *      Author: migue
 */

#include "Organizacion.h"
#include "Utilitario.h"
#include <sstream>
#include <iostream>


#define DIMENSION_FECHA "Fecha"


std::fstream Organizacion::_archModelo;
ConjuntoCampos Organizacion::_dimensiones;
ConjuntoCampos Organizacion::_hechos;
vectorCampos Organizacion::_campos;
std::string Organizacion::nombreNulo = STR_NULA;
bool Organizacion::_existeCampoEspecial;
unsigned Organizacion::_indEspecial;
Utilitario Organizacion::u;

void Organizacion::cargarDefiniciones(const std::string& rutaArchivo) {
	_dimensiones.clear();
	_hechos.clear();
	_campos.clear();
	_existeCampoEspecial = false;
	_indEspecial = 0;
	if (rutaArchivo.empty())
		_archModelo.open(RUTA_ARCH_MODELO);
	else
		_archModelo.open(rutaArchivo.c_str());


	if (_archModelo.is_open() == false) {
		// @todo TRATAR EL ERROR
		std::cerr << "Error al abrir el archivo de Modelo"<< std::endl;
	}
	else {

		char buff[500];
		if(_archModelo.good()) {

			_archModelo.getline(buff,500, '\n');
			std::string nombre = u.separar(buff, '=' , 0);
			std::string dim = u.separar(buff, '=' , 1);

			borrarCaracter(nombre, ' ');

			if (nombre == "Dimensiones") {
				borrarCaracter(dim, ' ');
				borrarCaracter(dim, '}');
				borrarCaracter(dim, '{');
				cargarDimensiones(dim);
			}
		}

		if (_archModelo.good()) {
			_archModelo.getline(buff,500, '\n');
			std::string nombre = u.separar(buff, '=' , 0);
			std::string hechos = u.separar(buff, '=' , 1);

			borrarCaracter(nombre, ' ');

			if (nombre == "Hechos") {
				borrarCaracter(hechos, ' ');
				borrarCaracter(hechos, '{');
				borrarCaracter(hechos, '}');
				cargarHechos(hechos);
			}
		}

		_archModelo.close();
	}
}

void Organizacion::cargarDimensiones(const std::string& dimensiones) {
	std::string dimNueva;
	dimNueva = u.separar(dimensiones, ',', 0);
	int ind = 0;
	//int id = 0;
	while (dimNueva.empty() == false) {
		if ((dimNueva==DIMENSION_FECHA) && !_existeCampoEspecial) {
			_existeCampoEspecial = true;
			_indEspecial = ind;
		}
		_dimensiones.insert(parDeConjunto(dimNueva, ind));
		_campos.push_back(dimNueva);

		ind++;
		dimNueva = u.separar(dimensiones, ',', ind);
	}

	/*
	ConjuntoCampos::iterator it;
	unsigned i;
	for (it = _dimensiones.begin() ,i = 0; it != _dimensiones.end() ; ++it, i++)
		it->second = i;
	*/
}

void Organizacion::cargarHechos(const std::string& hechos) {
	std::string hechoNuevo;
	hechoNuevo = u.separar(hechos, ',', 0);
	int ind = 0;
	while (hechoNuevo.empty() == false) {
		_hechos.insert(parDeConjunto(hechoNuevo, ind));
		_campos.push_back(hechoNuevo);
		ind++;
		hechoNuevo = u.separar(hechos, ',', ind);
	}
	/*
	ConjuntoCampos::iterator it;
	unsigned i;
	for (it = _hechos.begin() ,i = 0; it != _hechos.end() ; ++it, i++)
		it->second = i;
	*/
}

void Organizacion::borrarCaracter(std::string& palabra, const char caracter) {
	std::string aux;
	std::string parte = u.separar(palabra, caracter, 0);

	int i = 1;
	int cantBorrada = 0;
	do {
		cantBorrada++;
		aux += parte;
		parte = u.separar(palabra, caracter, i);
		i++;
	} while ((aux.size() + cantBorrada)< palabra.size());

	palabra = aux;
}


bool Organizacion::esDimension(const std::string& nombreCampo) {
	if (_dimensiones.find(nombreCampo) != _dimensiones.end())
		return true;
	else
		return false;
}

bool Organizacion::esHecho(const std::string& nombreCampo) {
	if (_hechos.find(nombreCampo) != _hechos.end())
		return true;
	else
		return false;
}

const std::string& Organizacion::nombreCampo(unsigned indice) {
	if (_campos.size() > indice)
		return _campos[indice];
	else
		return Organizacion::nombreNulo;
}

const std::string& Organizacion::nombreDimension(unsigned indice) {
	if (_dimensiones.size() > indice) {
		return _campos[indice];
	}
	else
		return Organizacion::nombreNulo;
}
const std::string& Organizacion::nombreHecho(unsigned indice){
	if (_hechos.size() > indice) {
		return _campos[indice + _dimensiones.size()];
	}
	else
		return Organizacion::nombreNulo;
}

unsigned Organizacion::cantidadHechos() {
	return _hechos.size();
}

unsigned Organizacion::cantidadDimensionesTotal() {
	return _dimensiones.size();
}

bool Organizacion::esDimensionEspecial(const std::string& nombreCampo) {
	return (nombreCampo == DIMENSION_FECHA);
}

unsigned Organizacion::indiceDeCampo(const std::string& campo) {
	if (_existeCampoEspecial && campo == DIMENSION_FECHA) {
		return _indEspecial;
	}

	if (_dimensiones.find(campo) != _dimensiones.end()) {
		return _dimensiones.find(campo)->second;
	}
	else if (_hechos.find(campo) != _hechos.end()) {
		return (_hechos.find(campo)->second + _dimensiones.size());
	}
	else {

		// @parahacer lanzar una excepcion
		return (unsigned)-1;
	}
}

unsigned Organizacion::cantidadCampos() {
	return (_campos.size());
}

unsigned Organizacion::indiceDeCampoSimple(const std::string& campo) {
	unsigned indice = (unsigned) -1;
	if (_dimensiones.find(campo) != _dimensiones.end()) {
		indice = _dimensiones.find(campo)->second;
		if (indice > _indEspecial && _existeCampoEspecial)
			indice--;

		return indice;
	}
	else if (_hechos.find(campo) != _hechos.end()) {
		indice = (_hechos.find(campo)->second + _dimensiones.size());
		if (_existeCampoEspecial)
			indice--;
		return indice;
	}
	else {
		return indice;
	}
}

const std::string& Organizacion::nombreDimensionSimple(unsigned indice) {
	if (_existeCampoEspecial && indice >= _indEspecial)
			indice++;

	if (_dimensiones.size() > indice)
		return _campos[indice];
	else
		return nombreNulo;

}

unsigned Organizacion::cantidadDimensionesSimples() {
	return 10;
	if (_existeCampoEspecial) {
		return _dimensiones.size() - 1;
	}
	else {
		return _dimensiones.size();
	}
}

unsigned Organizacion::cantidadCamposSimples() {
	if (_existeCampoEspecial)
		return _campos.size() - 1;
	else
		return _campos.size();
}

const std::string& Organizacion::nombreCampoSimple(unsigned indice) {
	if (_existeCampoEspecial && _campos.size() > indice) {
		if (indice < _indEspecial) {
			return _campos[indice];
		}
		else {
			return _campos[indice + 1];
		}
	}
	else {
		return nombreCampo(indice);
	}
}

