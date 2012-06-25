#include "AgenteRemoto.h"
#include <iostream>

void AgenteRemoto::detener_agente() {
	parar();
	agente->desconectar();
}

void AgenteRemoto::enviarRespuesta(Respuesta& r) {
    Lock l(m);
	if (agente && agente->conectado()) {
		if (!agente->enviar(r)) {
			detener_agente();
		}
	}
}

void AgenteRemoto::correr() {
	while (corriendo()) {
		if (agente && agente->conectado()) {
			ConsultaAgenteServidor parConsulta;
			parConsulta.first = this;
			if (agente->recibir(parConsulta.second)) {
				cconsultas.push(parConsulta);
			} else {
				parar();
			}
		} else {
			parar();
		}
	}
}

AgenteRemoto::AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr, ConsultasAgentesServidor& cons):
		agente(agt), blresolvedor(rentr), cconsultas(cons) {
}

AgenteRemoto::~AgenteRemoto() {
	detener_agente();
	delete agente;
}
