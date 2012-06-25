#ifndef _HILORESPONDERENTRADA_H
#define _HILORESPONDERENTRADA_H

#include "Definiciones.h"
#include "ResolvedorEntradas.h"
#include "Hilo.h"
#include "AgenteRemoto.h"

/* @DOC

	Clase HiloResponderEntrada

	Es la clase encargada de la resolucion de entradas del agente. Es una
clase heredera de hilo que hace las de consumer de la cola de entradas del
servidor. A su vez, se encarga de enviar la respuestas a traves del socket del
agente pertinente.

Atributos:
	
	ConsultasAgentesServidor& centradas: es una referencia a la cola de
	entradas del servidor. De aca obtendra las entradas a resolver. Notar
	que esta cola debe ser bloqueante en el metodo pop2.
	
	ResolvedorEntradas& resolvedor: es una referencia al objeto que se
	encargue de resolver las entradas.

@END*/

class HiloResponderEntrada: public Hilo {
private:
	ConsultasAgentesServidor& centradas;
	ResolvedorEntradas& resolvedor;
public:
/* @DOC
Metodos publicos:

 @END*/
 
/* @DOC
	HiloResponderEntrada(ConsultasAgentesServidor& centr, ResolvedorEntadas& rentr)
		Constructor de HiloResponderEntrada. Recibe las referencias
		correspondientes a la cola de entradas y al resolvedor.

	@END*/
	HiloResponderEntrada(ConsultasAgentesServidor& cconsultas, ResolvedorEntradas& rentr);
	~HiloResponderEntrada();
	
/* @DOC
	void correr()
		Es el metodo llamado por el callback del hilo. Es el encargado de
		sacar consultas de la cola, pedir la respuesta y enviarla a traves
		del AgenteRemoto correspondiente.		
	@END */
	void correr();
};

#endif
