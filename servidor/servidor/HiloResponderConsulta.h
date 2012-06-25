#ifndef _HILORESPONDERCONSULTA_H
#define _HILORESPONDERCONSULTA_H

#include "Definiciones.h"
#include "ResolvedorConsultas.h"
#include "Hilo.h"
#include "ClienteRemoto.h"

/* @DOC

	Clase HiloResponderConsulta

	Es la clase encargada de la resolucion de consultas del cliente. Es una
clase heredera de hilo que hace las de consumer de la cola de consultas del
servidor. A su vez, se encarga de enviar la consulta a traves del socket del
cliente requerido.

Atributos:
	
	ConsultasClientesServidor& cconsultas: es una referencia a la cola de
	consultas del servidor. De aca obtendra las consultas a resolver. Notar
	que esta cola debe ser bloqueante en el metodo pop2.
	
	ResolvedorConsultas& resolvedor: es una referencia al objeto que se
	encargue de resolver las consultas.

@END*/

class HiloResponderConsulta: public Hilo {
private:
	ConsultasClientesServidor& cconsultas;
	ResolvedorConsultas& resolvedor;
public:

/* @DOC
Metodos publicos:

 @END*/
 
/* @DOC
	HiloResponderConsulta(ConsultasClientesServidor& cconsultas, ResolvedorConsultas& rcons)
		Constructor de HiloResponderconsulta. Recibe las referencias
		correspondientes a la cola de consultas y al resolvedor.

	@END*/
	HiloResponderConsulta(ConsultasClientesServidor& cconsultas, ResolvedorConsultas& rcons);
	~HiloResponderConsulta();
	
	/* @DOC
	void correr()
		Es el metodo llamado por el callback del hilo. Es el encargado de
		sacar consultas de la cola, pedir la respuesta y enviarla a traves
		del ClienteRemoto correspondiente.		
	@END */
	void correr();
};

#endif
