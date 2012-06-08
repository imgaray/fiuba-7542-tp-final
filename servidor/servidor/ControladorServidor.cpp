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
		magentes.wait();
	magentes.lock();
	nact++;
	Respuesta r = rentr.resolverEntrada(entrada);
	nact--;
	mclientes.signal();
	magentes.signal();
	magentes.unlock();
	return r;
}
	
Respuesta ControladorServidor::resolver(Consulta& consulta) {
	cout << "nact = " << nact << " ncons = " << ncons << endl;
	while (nact != 0)
		mclientes.wait();
	mclientes.lock();
	ncons++;
	mclientes.unlock();
	Respuesta r = rcons.resolver(consulta);
	mclientes.lock();
	ncons--;
	magentes.signal();
	mclientes.signal();
	mclientes.unlock();
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
	Lock l(this->mclientes);
	clientes.push_back(rem);
}

void ControladorServidor::detener() {
	mclientes.lock();
	tclientes->detener_entrada();
	lclientes::iterator iter_clientes;
	for (iter_clientes = clientes.begin(); iter_clientes != clientes.end();
												++iter_clientes) {
		ClienteRemoto* crem = *iter_clientes;
		crem->detener_cliente();
	}

	mclientes.unlock();
	magentes.lock();
	tagentes->detener_entrada();
	lagentes::iterator iter_agentes;
	for (iter_agentes = agentes.begin(); iter_agentes != agentes.end();
												++iter_agentes) {
		AgenteRemoto* arem = *iter_agentes;
		arem->detener_agente();
	}
	magentes.unlock();
}

void ControladorServidor::agregarAgente(AgenteRemoto* agt) {
	Lock l(this->magentes);
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
