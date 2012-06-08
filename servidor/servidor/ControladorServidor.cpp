#include "ControladorServidor.h"
#include "BLMap.h"
#include "Mutex.h"
#include <iostream>
using namespace std;

void ControladorServidor::comenzar() {
	tagentes->iniciar();
	tclientes->iniciar();
}

Respuesta ControladorServidor::resolverEntrada(Consulta& entrada) {
	while (ncons != 0)
		m.wait();
	m.lock();
	nact++;
	Respuesta r = rentr.resolverEntrada(entrada);
	nact--;
	m.signal();
	m.unlock();
	return r;
}
	
Respuesta ControladorServidor::resolver(Consulta& consulta) {
	cout << "nact = " << nact << " ncons = " << ncons << endl;
	while (nact != 0)
		m.wait();
	m.lock();
	ncons++;
	m.unlock();
	Respuesta r = rcons.resolver(consulta);
	m.lock();
	ncons--;
	m.signal();
	m.unlock();
	return r;
}	

ControladorServidor::~ControladorServidor() {
	lclientes::iterator iter_clientes;
	for (iter_clientes = clientes.begin(); iter_clientes != clientes.end();
												++iter_clientes) {
		ClienteRemoto* crem = *iter_clientes;
		//clientes.erase(iter_clientes);
		delete crem;
	}
	lagentes::iterator iter_agentes;
	for (iter_agentes = agentes.begin(); iter_agentes != agentes.end();
												++iter_agentes) {
		AgenteRemoto* arem = *iter_agentes;
		//agentes.erase(iter_agentes);
		delete arem;
	}
	delete tagentes;
	delete tclientes;
}

void ControladorServidor::agregarCliente(ClienteRemoto* rem) {
	Lock l(this->m);
	clientes.push_back(rem);
}

void ControladorServidor::detener() {
	Lock l(m);
	lclientes::iterator iter_clientes;
	for (iter_clientes = clientes.begin(); iter_clientes != clientes.end();
												++iter_clientes) {
		ClienteRemoto* crem = *iter_clientes;
		crem->detener_cliente();
	}
	lagentes::iterator iter_agentes;
	for (iter_agentes = agentes.begin(); iter_agentes != agentes.end();
												++iter_agentes) {
		AgenteRemoto* arem = *iter_agentes;
		arem->detener_agente();
	}
	tagentes->detener_entrada();
	tagentes->detener_entrada();
}

void ControladorServidor::agregarAgente(AgenteRemoto* agt) {
	Lock l(this->m);
	agentes.push_back(agt);
}

ControladorServidor::ControladorServidor(ResolvedorConsultas& cons,
				ResolvedorEntradas& rent):
				 rcons(cons), rentr(rent) {
	ncons = 0;
	nact = 0;
	tagentes = new ThreadEntradaAgentes(*this, *this);
	tclientes = new ThreadEntradaClientes(*this, *this);
}
