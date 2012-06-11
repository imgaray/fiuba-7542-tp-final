#ifndef __SERVIDORREMOTO_H
#define __SERVIDORREMOTO_H

#include "Definiciones.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "ConsumerConsultas.h"
#include "ConsumerRespuestas.h"
#include "BLQueue.h"
#include "BLMap.h"
#include <utility>
#include <list>

class Consultante;

class ServidorRemoto {
private:
	// atributos contenedores
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	ConsumerRespuesta crespuesta;
	std::list<ConsumerConsulta*> cconsultas;

public:
	ServidorRemoto();
	~ServidorRemoto();

	void enviarConsulta(Consultante* consultante, Consulta consulta);
	void cancelarConsulta(unsigned IDcons);
};

#endif
