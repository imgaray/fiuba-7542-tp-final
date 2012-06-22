/*
 * ExhibidorRespuesta.cpp
 *
 *  Created on: 20/06/2012
 *      Author: migue
 */

#include "ExhibidorRespuesta.h"


ExhibidorRespuesta::ExhibidorRespuesta(FiltradoresPanel& filtrador) :
	_filtradores(filtrador){

}

ExhibidorRespuesta::~ExhibidorRespuesta() {
}

void ExhibidorRespuesta::hacerConsulta(ServidorRemoto& servidor) {
	this->consulta.limpiar();
	this->_filtradores.filtrar(this->consulta);
	servidor.enviarConsulta(this, this->consulta);
}

FiltradoresPanel& ExhibidorRespuesta::getFiltrador() {
	return this->_filtradores;
}
