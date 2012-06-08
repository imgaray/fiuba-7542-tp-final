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
#include "Mutex.h"
#include "../../comun/Definiciones.h"
#include <iostream>
using namespace std;

#define PORT_AGENTE (Puerto) 12345
#define PORT_CLIENTE (Puerto) 4321

class ThreadEntradaAgentes: public Hilo {
private:
	Socket* entradaAgentes;
	ContenedorAgentes& ca;	
	ResolvedorEntradas& re;
public:
	void correr() {
		while (corriendo()) {
			Socket* sagente = entradaAgentes->escucharConexion();
			if (sagente) {	
				AgenteRemoto* ag = new AgenteRemoto(sagente, re);
				ca.agregarAgente(ag);
				ag->iniciar();
			} else {
				detener_entrada();
			}
		}
	}
	
	void detener_entrada() {
		if (corriendo())
			parar();
		if (entradaAgentes)	
			entradaAgentes->desconectar();
		sincronizar();
	}
	
	ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent):
		ca(cag), re(rent) {
		entradaAgentes = new Socket(PORT_AGENTE);
		entradaAgentes->enlazar();
	}
	
	~ThreadEntradaAgentes() {
		detener_entrada();
		if (entradaAgentes)
			delete entradaAgentes;
	}
};

class ThreadEntradaClientes: public Hilo {
private:
	Socket* entradaClientes;
	ContenedorClientes& cc;
	ResolvedorConsultas& rc;
public:
	void correr() {
		while (corriendo()) {
			Socket* scliente = entradaClientes->escucharConexion();
			if (scliente) {
				ClienteRemoto* ag = new ClienteRemoto(scliente, rc);
				cc.agregarCliente(ag);
				ag->iniciar();
			} else {
				detener_entrada();
			}
		}
	}
	
	void detener_entrada() {
		if (corriendo())
			parar();
		if (entradaClientes)
			entradaClientes->desconectar();
		sincronizar();
	}
	
	ThreadEntradaClientes(ContenedorClientes& ccli, ResolvedorConsultas& rcons):
		cc(ccli), rc(rcons) {
		entradaClientes = new Socket(PORT_CLIENTE);
		entradaClientes->enlazar();
	}
	
	~ThreadEntradaClientes() {
		detener_entrada();
		if (entradaClientes)
			delete entradaClientes;
	}
};

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
	Mutex m;
//	Mutex magentes;
//	Mutex mclientes;
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
