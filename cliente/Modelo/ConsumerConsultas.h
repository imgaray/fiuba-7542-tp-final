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

/** @class ConsumerConsulta

	Esta clase es un consumer de consultas. Es decir, esta clase tiene
como responsabilidad consumir de la cola de consultas del cliente y enviarlas
al servidor. Al extender de Hilo, es un thread. El consumer se debe sincronizar
previo a su destrucción.
 */
	
class Socket;

class ConsumerConsulta: public Hilo {
private:
	ColaConsultas& consultas; 
	ColaRespuestas& respuestas; // deprecated.
	Socket*& servidor;
	BitmapCancelados& cancelados;
public:

/**	Es el método llamado por el callback del hilo. En el mismo
	es que se retira de la cola de consultas y se intentan enviar
	a través del socket. Si el envío falla, el hilo detiene su
	ejecución. */
	void correr();
	
	/** 
	@param cons Referencia a la cola de consultas del ServidorRemoto.
	@param resp (Deprecated) Referencia a la cola de respuestas del ServidorRemoto.
	@param conexion Socket del ServidorRemoto. Por el mismo se envían consultas.
	@param canc Bitmap de cancelados del ServidorRemoto.
	*/
	ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp,
							Socket*& conexion, BitmapCancelados& canc);
							
	/** Debe sincronizarse el hilo previo a su destrucción. */						
	~ConsumerConsulta();
};

#endif
