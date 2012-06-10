#ifndef __SERVIDORREMOTO_H
#define __SERVIDORREMOTO_H

#include "Consulta.h"
#include "Definiciones.h"
#include "Respuesta.h"
#include "BLQueue.h"
#include "BLMap.h"
#include <utility>

class Consultante;

class ServidorRemoto {
private:
	// atributos contenedores
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	friend ConsumerConsultas;
	friend ConsumerRespuestas;
	// faltaria ver donde van los hilos consumer/producer
public:
	ServidorRemoto();
	~ServidorRemoto();
	void enviarConsulta(Consultante* consultante, Consulta consulta) {
		if (!consultantes.has(consultante->getID())) {
			consultantes[consultante->getID()] = consultante;
		}
		ParConsulta par;
		par.first = consultante->getID();
		par.second = consulta;
		consultas.push(par);
	}
};

#endif
