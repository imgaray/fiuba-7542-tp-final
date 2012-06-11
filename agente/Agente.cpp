/*
 * Agente.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Agente.h"
#include <iostream>
#include "../comun/Organizacion.h"
#include "../comun/Definiciones.h"
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"

Agente::Agente(const std::string& huespedServidor) :
	_sck(PUERTO_ESTANDAR_AGENTE) {
	this->_huesped = huespedServidor;

}

Agente::~Agente() {
	// TODO Auto-generated destructor stub
}


void Agente::cargarDesdeConsola() {
	Consulta cons;

	bool seguirCargando = true;
	std::string campo;

	std::cout << ":::CARGA DE CAMPOS DESDE CONSOLA:::" << std::endl;

	while (seguirCargando) {
		cons.limpiar();
		for (unsigned i = 0; i < Organizacion::cantidadCampos() ; i++) {
			std::cout << "-";
			std::cout << Organizacion::nombreCampo(i) << ":";
			std::cin >> campo;

			cons.agregarCampo(campo);
		}

		//_sck.enviar(cons);

		// Comprobar la recepcion de Consulta

		//std::cin.seekg(0, std::ios::end);
		std::cout << "¿Ingresar otra Entrada? S/N" << std::endl;


		char aux;
		//aux = std::cin.peek();
		std::cin >> aux;
		seguirCargando = (aux == 's' || aux == 'S');

	}
}
