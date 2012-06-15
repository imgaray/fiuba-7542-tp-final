#include "AgenteRemoto.h"

void AgenteRemoto::detener_agente() {
	parar();
	if (agente)
		agente->desconectar();
	//sincronizar();
	this->parar();
}

void AgenteRemoto::correr() {
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

AgenteRemoto::AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr):
	agente(agt), blresolvedor(rentr) {
}

AgenteRemoto::~AgenteRemoto() {
	if (corriendo())
		detener_agente();
	if (agente)
		delete agente;
}
