#ifndef __SERVIDORREMOTO_H
#define __SERVIDORREMOTO_H

#include "Consulta.h"
#include "BLQueue.h"
#include "BLMap.h"
#include <utility>

class ServidorRemoto {
private:
	// Definiciones de tipos
	typedef std::pair<unsigned, Consulta> ParConsulta;
	typedef std::pair<unsigned, Respuesta> ParRespuesta;
	typedef BLQueue<ParConsulta> ColaConsultas;
	typedef BLQueue<ParRespuesta> ColaRespuestas;
	typedef BLMap<unsigned, Consultante*> MapaConsultantes;
	
	// atributos contenedores
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	
	// faltaria ver donde van los hilos consumer/producer
public:
	ServidorRemoto();
	~ServidorRemoto();
	// codigo, codigo everywhere! (Buzzlightyear)
};

#endif
