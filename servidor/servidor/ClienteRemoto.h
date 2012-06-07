#ifndef __CLIENTEREMOTO_H
#define __CLIENTEREMOTO_H

#include "Hilo.h"
#include "Socket.h"
#include "ResolvedorConsultas.h"
#include "Consulta.h"
#include "Respuesta.h"
#include <iostream>
using namespace std;

class ClienteRemoto: public Hilo {
private:
	Socket* cliente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorConsultas& blresolvedor;
public:

	void detener_cliente() {
		parar();
		if (cliente)
			cliente->desconectar();
		sincronizar();
	}
	
	void correr() {
		while (corriendo()) {
			Consulta c;
			bool valido = false;
			if (cliente->recibir(c)) {
				Respuesta r = blresolvedor.resolver(c);
				valido = cliente->enviar(r);
			}
			if (!valido) {
				detener_cliente();
			}
		}
	}
	
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons):
		cliente(cl), blresolvedor(rcons) {
	}
	
	~ClienteRemoto() {
		if (corriendo())
			detener_cliente();
		if (cliente)
			delete cliente;
	}
};

#endif
