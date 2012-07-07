#ifndef _HILORESPONDERCONSULTA_H
#define _HILORESPONDERCONSULTA_H

#include "Definiciones.h"
#include "ResolvedorConsultas.h"
#include "Hilo.h"
#include "ClienteRemoto.h"

/** @class HiloResponderConsulta

	Es la clase encargada de la resolución de consultas del cliente. Es una
clase heredera de hilo que hace las de consumer de la cola de consultas del
servidor. A su vez, se encarga de enviar la consulta a través del socket del
cliente requerido.

	
	ConsultasClientesServidor& cconsultas:	
	ResolvedorConsultas& resolvedor: 

@END*/

class HiloResponderConsulta: public Hilo {
private:
	ConsultasClientesServidor& cconsultas; /*  es una referencia a la cola de
	consultas del servidor. De aca obtendra las consultas a resolver. Debe ser
	bloqueante en pop2. */

	ResolvedorConsultas& resolvedor; /* es una referencia al objeto que se
	encargue de resolver las consultas. */

public:
 
/**	Constructor de HiloResponderconsulta.
 * @param cconsultas Cola de consultas del servidor. Debe ser bloqueante y thread
 * safe. @see BLQueue
 * @param rcons Objeto capaz de resolver una consulta.
 *  */
	HiloResponderConsulta(ConsultasClientesServidor& cconsultas, ResolvedorConsultas& rcons);
	
/** Destructor. Si esta corriendo, lo detiene. */	
	~HiloResponderConsulta();
	
	/**	Es el metodo llamado por el callback del hilo. Es el encargado de
		sacar consultas de la cola, pedir la respuesta y enviarla a través
		del ClienteRemoto correspondiente. */
	void correr();
};

#endif
