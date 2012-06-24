/*
 * ExhibidorRespuesta.cpp
 *
 *  Created on: 20/06/2012
 *      Author: migue
 */

#include "ExhibidorRespuesta.h"
#include "FiltradoresPanel.h"
#include "ServidorRemoto.h"
#include <iostream>

ExhibidorRespuesta::ExhibidorRespuesta(FiltradoresPanel& filtrador) :
	_filtradores(filtrador){

}

ExhibidorRespuesta::~ExhibidorRespuesta() {
}

void ExhibidorRespuesta::hacerConsulta(ServidorRemoto& servidor) {

	//std::cout << "-------------Exhibidor: Se entro al hacerConsulta" << std::endl;

	this->consulta.limpiar();
	this->_filtradores.filtrar(this->consulta);
	//servidor.enviarConsulta(this, this->consulta);
	Consultante::hacerConsulta(servidor);
}

FiltradoresPanel& ExhibidorRespuesta::getFiltrador() {
	return this->_filtradores;
}
