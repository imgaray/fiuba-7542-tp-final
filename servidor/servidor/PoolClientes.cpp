#include "PoolClientes.h"

#define MAX_HILOS 5

PoolClientes::PoolClientes(ResolvedorConsultas& resolvedor,
							ConsultasClientesServidor& consultas) {
	for (unsigned i = 0; i < MAX_HILOS_CLIENTE; i++) {
		hilos.push_back(new HiloResponderConsulta(consultas,resolvedor));
	}
}

PoolClientes::~PoolClientes() {
	detener();
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		delete (*iter);
	}
}

void PoolClientes::detener() {
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->parar();
		(*iter)->sincronizar();
	}
}

void PoolClientes::iniciar() {
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->iniciar();
	}
}
