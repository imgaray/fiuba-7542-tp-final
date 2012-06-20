#ifndef __CONSUMERCONSULTAS_H
#define __CONSUMERCONSULTAS_H

#include "Definiciones.h"
#include "Hilo.h"
#include "Respuesta.h"
#include "Consulta.h"
#include "Socket.h"
#include "ArchivoConfiguracion.h"
#include <cerrno>
#include <cstring>
#include <string>
#define MAX_OPEN_PORTS 1


class Socket;

class ConsumerConsulta: public Hilo {
private:
	ColaConsultas& consultas;
	ColaRespuestas& respuestas;
	Socket*& servidor;
	BitmapCancelados& cancelados;
public:
	void correr();
	ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp,
							Socket*& conexion, BitmapCancelados& canc);
	~ConsumerConsulta();
};

#endif
