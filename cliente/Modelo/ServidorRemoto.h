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
#include "Socket.h"

class Consultante;

class ServidorRemoto {
private:
	// atributos contenedores
	Socket* sock;
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	ConsumerRespuesta crespuesta;
	ConsumerConsulta cconsulta;

public:
	ServidorRemoto();
	~ServidorRemoto();
	void conectar() throw(char* );
	void enviarConsulta(Consultante* consultante, Consulta consulta);
	void cancelarConsulta(unsigned IDcons);
};

#endif
