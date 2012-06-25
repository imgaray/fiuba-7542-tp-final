#ifndef _POOLCLIENTES_H
#define _POOLCLIENTES_H

#define MAX_HILOS_CLIENTE 3

#include "Definiciones.h"
#include <list>
#include "HiloResponderConsulta.h"
#include "ResolvedorConsultas.h"

/* @DOC

	Clase PoolClientes
	
	Es una clase que tiene una determinada cantidad de workers que consumen
de la cola de clientes. No es mas que una forma de encapsular una lista que
contiene N instancias de HiloResponderConsulta.

	Sus unicos metodos, detener() e iniciar() se encargan de detener e
iniciar los hilos que contenga en su lista.
	@END
	*/

class PoolClientes {
private:
	std::list<HiloResponderConsulta*> hilos;
public:
	PoolClientes(ResolvedorConsultas& resolvedor, ConsultasClientesServidor& entradas);
	~PoolClientes();
	void detener();
	void iniciar();
};

#endif
