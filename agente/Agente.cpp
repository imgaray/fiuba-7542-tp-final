/*
 * Agente.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Agente.h"
#include <iostream>
#include "../comun/Socket.h"
#include "../comun/Organizacion.h"
#include "../comun/Definiciones.h"
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"
#include "../comun/Utilitario.h"
#include <stdlib.h>
#include "ArchivoConfiguracion.h"

#define T_BUFFER 256
#define TABULADOR '\t'

Agente::Agente(const std::string& rutaConfig) {
	Organizacion::cargarDefiniciones(RUTA_ARCH_MODELO);
	this->_sck = NULL;
	this->cargarConfiguracion(rutaConfig);
}

Agente::~Agente() {
	if (_sck->conectado())
		_sck->desconectar();

	delete this->_sck;
}


void Agente::cargarConfiguracion(const std::string& rutaConfig) {
	Puerto puerto;
	ArchivoConfiguracion arch("agente.conf");
	std::string atrpuerto = PUERTO_AGENTE_ATR;
	std::string atrhuesped = HOST_AGENTE_ATR;
	_huesped = arch.obtenerAtributo(atrhuesped);
	if (_huesped.size() == 0) {
		_huesped = "localhost";
		std::cout << "entre al caso default del huesped"<<std::endl;
	}
	std::string spuerto = arch.obtenerAtributo(atrpuerto);
	Utilitario u;
	u.borrarCaracter(_huesped, '\n');
	if (spuerto.size()) {
		puerto = (Puerto) u.convertirAEntero(spuerto);
	}
	else {
		puerto = PUERTO_ESTANDAR_AGENTE;
	}
	std::cout << "Puerto:  -"<< puerto <<"-"<< std::endl;
	std::cout << "Huesped: -"<< _huesped<<"- size = " << _huesped.size() << std::endl;


	this->_sck = new Socket(puerto);

	this->_sck->conectar(_huesped);
}

void Agente::cargarDesdeConsola() {
	Consulta cons;

	bool seguirCargando = true;
	std::string campo;

	std::cout << ":::CARGA DE CAMPOS DESDE CONSOLA:::" << std::endl;

	while (seguirCargando && _sck->conectado()) {
		cons.limpiar();
        cons.definirComoConsultaAgente();
		for (unsigned i = 0; i < Organizacion::cantidadCampos() ; i++) {
			std::cout << "-";
			std::cout << Organizacion::nombreCampo(i) << ":";
			std::getline(std::cin, campo);

			cons.agregarCampo(campo);
		}


		this->enviarConsulta(cons);
		this->recibirRespuesta();

		std::cout << "¿Ingresar otra Entrada? S/N" << std::endl;


		std::string aux;
		std::getline(std::cin, aux);
		seguirCargando = (aux == "s" || aux == "S");
	}
}

void Agente::cargarDesdeArchivo(const std::string& rutaDatos) {
	std::fstream archivo(rutaDatos.c_str(), std::fstream::in);
	Consulta cons;
	std::string linea;
	std::string campo;
	Utilitario util;

	while (archivo.good() && _sck->conectado()) {
		cons.limpiar();
		cons.definirComoConsultaAgente();

		leerLinea(archivo, linea);

		if (linea.size() > 0) {

			for (unsigned i = 0 ; i < Organizacion::cantidadCampos() ; i++) {
				campo = util.separar(linea, TABULADOR, i);
				cons.agregarCampo(campo);
			}

			this->enviarConsulta(cons);
		}
	}

	this->recibirRespuesta();
}



void Agente::leerLinea(std::fstream& archivo, std::string& linea) {
	linea.clear();

	char buffer[T_BUFFER];

	bool seguirLeyendo = true;
	do {
		archivo.getline(buffer, T_BUFFER, '\n');
		linea.append(buffer, archivo.gcount());

		seguirLeyendo = (archivo.gcount() == T_BUFFER);

		if (archivo.bad())
			archivo.clear();

	} while (seguirLeyendo);
}

void Agente::enviarConsulta(const Consulta& consulta) {
	if (this->_sck->conectado()) {
		this->_sck->enviar(consulta);
	}
}

void Agente::recibirRespuesta() {
	Respuesta resp;
	this->_sck->recibir(resp);

	std::cout << resp.mensajeInterno() << std::endl;
}

