#ifndef _POOLAGENTES_H
#define _POOLAGENTES_H

#include "Definiciones.h"
#include <list>
#include "HiloResponderEntrada.h"
#include "ResolvedorEntradas.h"

/** @class PoolAgentes
	
	Es una clase que tiene una determinada cantidad de workers que consumen
de la cola de agentes. No es más que una forma de encapsular una lista que
contiene N instancias de HiloResponderEntrada.

	Sus únicos metodos, detener() e iniciar() se encargan de detener e
iniciar los hilos que contenga en su lista. */

class PoolAgentes {
private:
	std::list<HiloResponderEntrada*> hilos; /* Lista que contiene todos los
	workers */
	
public:
	/** En el constructor es que se popula la lista de hilos
	 * @param resolvedor Objeto capaz de resolver entradas.
	 * @param entradas Cola de entradas de agente del servidor. */
	PoolAgentes(ResolvedorEntradas& resolvedor, ConsultasAgentesServidor& entradas);
	
	/** Detiene todos sus workers y los elimina */
	~PoolAgentes();
	
	/** Detiene la ejecución de todos sus workers. */
	void detener();
	
	/** Comienza la ejecución de todos sus workers. */
	void iniciar();
};

#endif
