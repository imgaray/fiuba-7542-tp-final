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
#include <string>

class Consultante;

class ServidorRemoto {
private:
	// atributos contenedores
	ColaConsultas consultas;
	ColaRespuestas respuestas;
	MapaConsultantes consultantes;
	BitmapCancelados cancelados;
	ConsumerRespuesta crespuesta;
	ConsumerConsulta cconsulta;
	Socket* sock;
	std::string sdireccion;

public:
	
	ServidorRemoto();
	~ServidorRemoto();
	void conectar() throw();
	void enviarConsulta(Consultante* consultante, Consulta consulta);
	void cancelarConsulta(unsigned IDcons);
};

#endif
