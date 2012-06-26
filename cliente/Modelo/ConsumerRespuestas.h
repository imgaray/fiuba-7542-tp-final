#ifndef __CONSUMERRESPUESTA_H
#define __CONSUMERRESPUESTA_H

#include "Definiciones.h"
#include "BLQueue.h"
#include "Hilo.h"
#include "Mutex.h"
#include "Socket.h"

/*
@DOC

	Clase ConsumerRespuesta

	Esta clase es un consumer de respuestas. Es decir, esta clase tiene
como responsabilidad consumir del socket que esta conectado al servidor
y encolarlas en la cola de respuestas del cliente. Al extender de Hilo,
es un thread, entonces el consumer debe ser sincronizado previo a su destruccion.

	Atributos
	
	ColaRespuestas& consultas: Es la cola de respuestas del cliente. Esta cola
	debe ser thread safe.
	
	Socket*& servidor: Es el socket que esta conectado con el servidor.
	A traves del mismo se esperaran las respuestas a las consultas enviadas.

	BitmapCancelados& cancelados: Es un bitmap de consultas canceladas.
	Cada vez que se obtiene una respuesta, se verifica que no este
	cancelada antes de encolarla.
	
@END */

class ConsumerRespuesta: public Hilo {
private:
	ColaRespuestas& respuestas;
	MapaConsultantes& consultantes;
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
			se espera por una respuesta del socket. Si recibe exitosamente
			encola la respuesta en la cola de respuestas del cliente.
			Si falla la recepcion, el hilo procedera a detener su ejecucion.
@END*/

	void correr();
	ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons,
							Socket*& conexion, BitmapCancelados& canc);
	~ConsumerRespuesta();

};

#endif
