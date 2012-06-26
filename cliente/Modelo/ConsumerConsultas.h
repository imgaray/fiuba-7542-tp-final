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

/*
@DOC

	Clase ConsumerConsulta

	Esta clase es un consumer de consultas. Es decir, esta clase tiene
como responsabilidad consumir de la cola de consultas del cliente y enviarlas
al servidor. Al extender de Hilo, es un thread. El consumer se debe sincronizar
previo a su destruccion.

	Atributos
	
	ColaConsultas& consultas: Es la cola de consultas del cliente. Esta cola
	debe ser bloqueante.
	
	Socket*& servidor: Es el socket que esta conectado con el servidor.
	A traves del mismo se enviaran las respuestas obtenidas de la cola.
	BitmapCancelados& cancelados: Es un bitmap de consultas canceladas.
	Cada vez que se saca una consulta de la cola, se verifica que no este
	cancelada antes de enviarla.
	

@END */

class Socket;

class ConsumerConsulta: public Hilo {
private:
	ColaConsultas& consultas;
	ColaRespuestas& respuestas;
	Socket*& servidor;
	BitmapCancelados& cancelados;
public:
/*
@DOC
	Metodos publicos
	
@END
*/

/*@DOC
		void correr():
			Es el metodo llamado por el callback del hilo. En el mismo
			es que se retira de la cola de consultas y se intentan enviar
			a traves del socket. Si el envio falla, el hilo detiene su
			ejecucion.
@END*/
	void correr();
	ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp,
							Socket*& conexion, BitmapCancelados& canc);
	~ConsumerConsulta();
};

#endif
