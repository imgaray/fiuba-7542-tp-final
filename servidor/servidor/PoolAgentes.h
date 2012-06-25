#ifndef _POOLAGENTES_H
#define _POOLAGENTES_H

// #define MAX_HILOS 1  // pongo esta linea en el .cpp

#include "Definiciones.h"
#include <list>
#include "HiloResponderEntrada.h"
#include "ResolvedorEntradas.h"

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
