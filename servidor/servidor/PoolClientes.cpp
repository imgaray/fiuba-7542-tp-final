#include "PoolClientes.h"

PoolClientes::PoolClientes(ResolvedorConsultas& resolvedor,
							ConsultasClientesServidor& consultas) {
	for (unsigned i = 0; i < MAX_HILOS; i++) {
		hilos.push_back(new HiloResponderConsulta(consultas,resolvedor));
	}
}

PoolClientes::~PoolClientes() {
	detener();
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->sincronizar();
		 delete (*iter);
	}
}

void PoolClientes::detener() {
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->parar();
	}
}

void PoolClientes::iniciar() {
	std::list<HiloResponderConsulta*>::iterator iter;
	for (iter = hilos.begin(); iter != hilos.end(); ++iter) {
		(*iter)->iniciar();
	}
}
