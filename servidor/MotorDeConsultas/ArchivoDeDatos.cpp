/*
 * ArchivoDeDatos.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "ArchivoDeDatos.h"
#include <iostream>
#include "../../comun/Definiciones.h"

#define RUTA_POSCIONES_RELATIVAS "-id.dat"
#define RUTA_ARCHIVO_DATOS "./datos.txt"

#define fin_reg sep_tipo
#define TAM_BUFFER 500

ArchivoDeDatos::ArchivoDeDatos(const std::string& ruta) {
	_archivoPrincipal.open(ruta.c_str(), std::fstream::out | std::fstream::in | std::fstream::binary);
	if (_archivoPrincipal.is_open() == false) {
		_archivoPrincipal.open(ruta.c_str(),std::fstream::out);
		_archivoPrincipal.close();
		_archivoPrincipal.open(ruta.c_str(),std::fstream::out | std::fstream::in | std::fstream::binary);
	}

	std::string rutaIDs = ruta;
	rutaIDs += RUTA_POSCIONES_RELATIVAS;
	_posRelativas.open(rutaIDs.c_str(), std::fstream::binary | std::fstream::in | std::fstream::out);
	if (_posRelativas.is_open() == false) {
		_posRelativas.open(rutaIDs.c_str(),std::fstream::out);
		_posRelativas.close();
		_posRelativas.open(rutaIDs.c_str(), std::fstream::out | std::fstream::in | std::fstream::binary);
	}

	Id_Registro id;

	if (_posRelativas.good()) {
		_posRelativas.seekg(0, std::ios::end);
		size_t tamArchivo = _posRelativas.tellg();

		if (tamArchivo > sizeof(Id_Registro) ) {
			_posRelativas.seekg(0, std::ios::beg);
			_posRelativas.read((char*)&id, sizeof(Id_Registro));
			_ultimoID = id;
		}
		else {
			_ultimoID = 0;
			_posRelativas.seekp(0, std::ios::beg);
			_posRelativas.write((char*)&_ultimoID, sizeof(Id_Registro));
			_posRelativas.seekp(sizeof(_ultimoID), std::ios::beg);
			_posRelativas.write((char*)&_ultimoID, sizeof(Id_Registro));
			_posRelativas.flush();
		}

	} else {
		_ultimoID = 0;
	}
}

ArchivoDeDatos::~ArchivoDeDatos() {

	if (_posRelativas.good()) {
		_posRelativas.seekp(0, std::ios::beg);
		_posRelativas.write((char*)&_ultimoID, sizeof(size_t));

	}
	else {
		std::cout << "Error en archivo de posiciones" << std::endl;
	}
	_archivoPrincipal.close();
	_posRelativas.close();
}


size_t ArchivoDeDatos::cantidadRegistros() {
	return _ultimoID;
}

Id_Registro ArchivoDeDatos::guardarRegistro(const std::string & registro) {
	std::string regAGuardar = registro;
	regAGuardar += fin_reg;
	size_t tamRegNuevo = regAGuardar.size();
	size_t posicion = 0;

	if (_posRelativas.fail())
		_posRelativas.clear();

	_posRelativas.seekg((_ultimoID + 1) * sizeof(size_t), std::ios::beg);
	_posRelativas.read((char*) &posicion, sizeof(size_t));

	if (_archivoPrincipal.fail())
		_archivoPrincipal.clear();
	_archivoPrincipal.seekp(posicion , std::ios::beg);
	_archivoPrincipal.write(regAGuardar.c_str(), tamRegNuevo);
	_archivoPrincipal.flush();

	Id_Registro aux = _ultimoID;

	_ultimoID++;

	size_t nuevaPosicion = tamRegNuevo + posicion;
	_posRelativas.seekp((_ultimoID + 1) * sizeof(size_t), std::ios::beg);
	_posRelativas.write((char*)&nuevaPosicion, sizeof(size_t));

	return aux;
}

std::string ArchivoDeDatos::obtenerRegistro(Id_Registro id) {
	if (id < _ultimoID) {
		size_t posicion;
		if (_posRelativas.fail())
			_posRelativas.clear();

		_posRelativas.seekg((id + 1)* sizeof(size_t), std::ios::beg);
		_posRelativas.read((char*)&posicion, sizeof(size_t));

		std::string reg;
		leerRegistro(posicion, reg);

		return reg;
	}

	return "";
}

void ArchivoDeDatos::leerRegistro(const size_t& posicion, std::string& reg) {
	char buffer[TAM_BUFFER];

	reg.clear();
	size_t bytesLeidos = 0;
	if (_archivoPrincipal.fail())
		_archivoPrincipal.clear();


	_archivoPrincipal.seekg(posicion, std::ios::beg);
	do {
		_archivoPrincipal.read(buffer, TAM_BUFFER);
		reg += buffer;
		bytesLeidos += _archivoPrincipal.gcount();
		_archivoPrincipal.seekg(posicion + bytesLeidos, std::ios::beg);
		reg.resize(bytesLeidos);
	} while (reg.find(fin_reg, bytesLeidos) != std::string::npos);

	size_t posFin = reg.find(fin_reg, 0);
	if (posFin != std::string::npos)
		reg.resize(posFin);

	if (_archivoPrincipal.fail())
		_archivoPrincipal.clear();
}
