#include "PoolAgentes.h"

#define MAX_HILOS_AGENTE 3

PoolAgentes::PoolAgentes(ResolvedorEntradas& resolvedor,
							ConsultasAgentesServidor& entradas) {
	for (unsigned i = 0; i < MAX_HILOS_AGENTE; i++) {
		hilos.push_back(new HiloResponderEntrada(entradas,resolvedor));
	}
}

PoolAgentes::~PoolAgentes() {
	detener();
	std::list<HiloResponderEntrada*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->sincronizar();
		 delete (*iter);
	}
}

void PoolAgentes::detener() {
	std::list<HiloResponderEntrada*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->parar();
	}
}

void PoolAgentes::iniciar() {
	std::list<HiloResponderEntrada*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->iniciar();
	}
}
