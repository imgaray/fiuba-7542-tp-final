#ifndef __AGENTEREMOTO_H
#define __AGENTEREMOTO_H

#include "Hilo.h"
#include "Socket.h"
#include "ResolvedorEntradas.h"
#include "Consulta.h"
#include "Respuesta.h"

class AgenteRemoto: public Hilo {
private:
	Socket* agente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorEntradas& blresolvedor;
public:
	void detener_agente() {
		parar();
		if (agente)
			agente->desconectar();
		sincronizar();
	}
	
	void correr() {
		while (corriendo()) {
			Consulta c;
			bool valido = false;
			if (agente->recibir(c)) {
				Respuesta r = blresolvedor.resolverEntrada(c);
				valido = agente->enviar(r);
			}
			if (!valido) {
				detener_agente();
			}
		}
	}
	
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr):
		agente(agt), blresolvedor(rentr) {
	}
	
	~AgenteRemoto() {
		if (corriendo())
			detener_agente();
		if (agente)
			delete agente;
	}
};

#endif
