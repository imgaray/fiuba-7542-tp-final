#ifndef __CONTROLADOR_H
#define __CONTROLADOR_H

#include "BLQueue.h"
#include "BLMap.h"
#include <utility>
#include <list>
#include "ClienteRemoto.h"
#include "AgenteRemoto.h"
#include "ContenedorAgentes.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "../../comun/Consulta.h"
#include "ThreadEntradaAgentes.h"
#include "ThreadEntradaClientes.h"
#include "Mutex.h"
#include "../../comun/Definiciones.h"
#include <iostream>
using namespace std;

class ControladorServidor:  public ResolvedorConsultas, 
							public ResolvedorEntradas,
							public ContenedorClientes,
							public ContenedorAgentes {
private:
	// atributos
//	typedef std::pair<unsigned, Consulta> parConsulta;
//	BLQueue<parConsulta> consultas;
//	BLQueue<parConsulta> actualizaciones;
	typedef std::list<ClienteRemoto*> lclientes;
	typedef std::list<AgenteRemoto*> lagentes;
	unsigned int ncons;
	unsigned int nact;
	lclientes clientes;
	lagentes agentes;
//	BLMap<unsigned, ClienteRemoto*> clientes;
//	BLMap<unsigned, AgenteRemoto*> agentes;
	ResolvedorConsultas& rcons;
	ResolvedorEntradas& rentr;
//	ManejadorIds mids;
	ThreadEntradaAgentes* tagentes;
	ThreadEntradaClientes* tclientes;
//	Mutex m;
	Mutex magentes;
	Mutex mclientes;
public:
	Respuesta resolverEntrada(Consulta& entrada);
	Respuesta resolver(Consulta& consulta);
	ControladorServidor(ResolvedorConsultas& cons, ResolvedorEntradas& rent);
	~ControladorServidor();
	void agregarCliente(ClienteRemoto* rem);
	void agregarAgente(AgenteRemoto* agt);
	void comenzar();
	void detener();
};

#endif
