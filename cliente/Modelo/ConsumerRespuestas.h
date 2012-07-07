#ifndef __CONSUMERRESPUESTA_H
#define __CONSUMERRESPUESTA_H

#include "Definiciones.h"
#include "BLQueue.h"
#include "Hilo.h"
#include "Mutex.h"
#include "Socket.h"

/** @class ConsumerRespuesta

	Esta clase es un consumer de respuestas. Es decir, esta clase tiene
como responsabilidad consumir del socket que está conectado al servidor
y encolarlas en la cola de respuestas del cliente. Al extender de Hilo,
es un thread, entonces el consumer debe ser sincronizado previo a su destrucción.
*/

	
class ConsumerRespuesta: public Hilo {
private:
	ColaRespuestas& respuestas;
	MapaConsultantes& consultantes;
	Socket*& servidor;
	BitmapCancelados& cancelados;

public:
/**	Es el método llamado por el callback del hilo. En el mismo
	se espera por una respuesta del socket. Si recibe exitosamente
	encola la respuesta en la cola de respuestas del cliente.
	Si falla la recepción, el hilo procederá a detener su ejecución. */
	void correr();
	
/** @param cresp Cola de respuestas del servidor.
 * @param mcons (deprecated) mapa de consultantes del servidor.
 * @param conexion Socket del ServidorRemoto conectado al servidor.
 * @param canc Bitmap de consultas canceladas. */	
	ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons,
							Socket*& conexion, BitmapCancelados& canc);
	
	/** Debe sincronizarse el hilo antes de ser destruido. */
	~ConsumerRespuesta();
};

#endif
