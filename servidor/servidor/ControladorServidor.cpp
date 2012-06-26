#include "ControladorServidor.h"
//#include "BLMap.h"
#include "Mutex.h"
#include <iostream>
using namespace std;

bool ControladorServidor::activo() {
	return tagentes->activo() && tclientes->activo();
}

void ControladorServidor::comenzar() {
	tagentes->iniciar();
	tclientes->iniciar();
	poolclientes.iniciar();
	poolagentes.iniciar();
}

Respuesta ControladorServidor::resolverEntrada(Consulta& entrada) {
	m.lock();
	while (ncons != 0) {
		cout << "Ciclo wait de resolver entrada de controladorservidor" << endl;
		m.wait();
	}
	nact++;
	Respuesta r = rentr.resolverEntrada(entrada);
	nact--;
	m.signal();
	m.unlock();
	return r;
}

Respuesta ControladorServidor::resolver(Consulta& consulta) {
	m.lock();
	while (nact != 0) {
		cout << "Ciclo wait de resolver consulta de controladorservidor" << endl;
		m.wait();
	}
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
		delete crem;
	}
	lagentes::iterator iter_agentes;
	for (iter_agentes = agentes.begin(); iter_agentes != agentes.end();
												++iter_agentes) {
		AgenteRemoto* arem = *iter_agentes;
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
	m.lock();
	// detengo las entradas
	centradas.close();
	cconsultas.close();
	tclientes->detener_entrada();
	tagentes->detener_entrada();
	poolagentes.detener();
	poolclientes.detener();
	tclientes->sincronizar();
	tagentes->sincronizar();
	// detengo los clientes
	lclientes::iterator iter_clientes;
	for (iter_clientes = clientes.begin(); iter_clientes != clientes.end();
												++iter_clientes) {
		ClienteRemoto* crem = *iter_clientes;
		crem->detener_cliente();
		crem->sincronizar();
	}
	// detengo los agentes
	lagentes::iterator iter_agentes;
	for (iter_agentes = agentes.begin(); iter_agentes != agentes.end();
												++iter_agentes) {
		AgenteRemoto* arem = *iter_agentes;
		arem->detener_agente();
		arem->sincronizar();
	}
	m.unlock();
}

void ControladorServidor::agregarAgente(AgenteRemoto* agt) {
	Lock l(this->m);
	agentes.push_back(agt);
}

ControladorServidor::ControladorServidor(ResolvedorConsultas& cons,
				ResolvedorEntradas& rent, Puerto pcl, Puerto pag):
				 puerto_clientes(pcl),
				 puerto_agentes(pag),
				 rcons(cons), rentr(rent),
				 poolclientes(*this, cconsultas),
				 poolagentes(*this, centradas) {

	ncons = 0;
	nact = 0;
	tagentes = new ThreadEntradaAgentes(*this, *this, puerto_agentes, centradas);
	tclientes = new ThreadEntradaClientes(*this, *this, puerto_clientes, cconsultas);
}
