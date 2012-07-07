#ifndef _POOLCLIENTES_H
#define _POOLCLIENTES_H

#define MAX_HILOS_CLIENTE 5

#include "Definiciones.h"
#include <list>
#include "HiloResponderConsulta.h"
#include "ResolvedorConsultas.h"

/** @class PoolClientes
	
	Es una clase que tiene una determinada cantidad de workers que consumen
de la cola de clientes. No es más que una forma de encapsular una lista que
contiene N instancias de HiloResponderConsulta.

	Sus únicos metodos, detener() e iniciar() se encargan de detener e
iniciar los hilos que contenga en su lista. */

class PoolClientes {
private:
	std::list<HiloResponderConsulta*> hilos; /* Lista que contiene todos sus
	workers */
	
public:

	/** Popula la lista de workers.
	 * @param resolvedor Objeto capaz de resolver consultas.
	 * @param entradas Referencia a la cola de consultas de clientes del servidor.
	 */
	PoolClientes(ResolvedorConsultas& resolvedor, ConsultasClientesServidor& entradas);

	/** Si esta en ejecución, detiene todos sus wworkers. Libera la memoria de los workers */
	~PoolClientes();
	
	/** Detiene la ejecución de los workers. */
	void detener();
	
	/** Comienza la ejecución de los workers. */
	void iniciar();
};

#endif
