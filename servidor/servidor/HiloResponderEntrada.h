#ifndef _HILORESPONDERENTRADA_H
#define _HILORESPONDERENTRADA_H

#include "Definiciones.h"
#include "ResolvedorEntradas.h"
#include "Hilo.h"
#include "AgenteRemoto.h"

/** @class HiloResponderEntrada

	Es la clase encargada de la resolución de entradas del agente. Es una
clase heredera de hilo que hace las de consumer de la cola de entradas del
servidor. A su vez, se encarga de enviar la respuestas a través del socket del
agente pertinente. */

class HiloResponderEntrada: public Hilo {
private:
	
	ConsultasAgentesServidor& centradas; /* es una referencia a la cola de
	entradas del servidor. De aca obtendra las entradas a resolver. Notar
	que esta cola debe ser bloqueante en el metodo pop2. */
	
	ResolvedorEntradas& resolvedor; /* es una referencia al objeto que se
	encargue de resolver las entradas. */

public:
/**	Constructor de HiloResponderEntrada.
 * @param cconsultas Referencia a la cola de entradas del servidor. Debe ser
 * bloqueante y thread safe. @see BLQueue
 * @param rentr Objeto capaz de resolver entradas. */
	HiloResponderEntrada(ConsultasAgentesServidor& cconsultas, ResolvedorEntradas& rentr);
	
	/** Destructor. Si esta corriendo, detiene la ejecucion del hilo. */
	~HiloResponderEntrada();
	
/**	Es el método llamado por el callback del hilo. Es el encargado de
	sacar consultas de la cola, pedir la respuesta y enviarla a traves
	del AgenteRemoto correspondiente. */
	void correr();
};

#endif
