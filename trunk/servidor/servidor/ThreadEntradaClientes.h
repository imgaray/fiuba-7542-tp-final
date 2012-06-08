#ifndef __THREADENTRADACLIENTES__H
#define __THREADENTRADACLIENTES__H

#include "Socket.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ClienteRemoto.h"
#include "Hilo.h"

#define PORT_CLIENTE (Puerto) 4321

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

#endif
