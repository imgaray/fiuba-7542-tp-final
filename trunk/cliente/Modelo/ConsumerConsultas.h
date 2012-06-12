#ifndef __CONSUMERCONSULTAS_H
#define __CONSUMERCONSULTAS_H

#include "Definiciones.h"
#include "Hilo.h"
#include "Respuesta.h"
#include "Consulta.h"
#include "Socket.h"
#include "ArchivoConfiguracion.h"
#define MAX_OPEN_PORTS 10
#define RUTACONFIGURACIONSR "serverRemoto.conf"
#define ATRIBPUERTO "puerto_servidor"
#define ATRIBDIRECCION "direccion_servidor"

class Socket;

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
