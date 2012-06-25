#ifndef _POOLAGENTES_H
#define _POOLAGENTES_H

// #define MAX_HILOS 1  // pongo esta linea en el .cpp

#include "Definiciones.h"
#include <list>
#include "HiloResponderEntrada.h"
#include "ResolvedorEntradas.h"

/* @DOC

	Clase PoolAgentes
	
	Es una clase que tiene una determinada cantidad de workers que consumen
de la cola de agentes. No es mas que una forma de encapsular una lista que
contiene N instancias de HiloResponderEntrada.

	Sus unicos metodos, detener() e iniciar() se encargan de detener e
iniciar los hilos que contenga en su lista.
	@END
	*/

class PoolAgentes {
private:
	std::list<HiloResponderEntrada*> hilos;
public:
	PoolAgentes(ResolvedorEntradas& resolvedor, ConsultasAgentesServidor& entradas);
	~PoolAgentes();
	void detener();
	void iniciar();
};

#endif
