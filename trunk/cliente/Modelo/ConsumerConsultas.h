#ifndef __CONSUMERCONSULTAS_H
#define __CONSUMERCONSULTAS_H

#include "Socket.h"
#include "Definiciones.h"
#include "Hilo.h"
#include "Respuesta.h"
#include "Consulta.h"
#define MAX_OPEN_PORTS 10

class ConsumerConsulta: public Hilo {
private:
	Socket* servidor;
	ColaConsultas& consultas;
	ColaRespuestas& respuestas;
public:
	void detener_hilo();
	
	void correr();
	
	ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp);
	
	~ConsumerConsulta();
};

#endif
