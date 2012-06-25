#ifndef _POOLCLIENTES_H
#define _POOLCLIENTES_H

// #define MAX_HILOS 5 pongo esta linea en el .cpp

#include "Definiciones.h"
#include <list>
#include "HiloResponderConsulta.h"
#include "ResolvedorConsultas.h"

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
