#include "ClienteRemoto.h"
#include <iostream>

void ClienteRemoto::correr() {
	while (corriendo()) {
		if (cliente && cliente->conectado()) {
			ConsultaClienteServidor parConsulta;
			parConsulta.first = this;
			if (cliente->recibir(parConsulta.second)) {
				cs.push(parConsulta);
			}
			else {
				parar();
			}
		} else {
			parar();
		}
	}
}

void ClienteRemoto::enviarRespuesta(Respuesta& r) {
    Lock l(m);
	if (cliente && cliente->conectado()) {
		if (!cliente->enviar(r)) {
			detener_cliente();
		}
	}
}


void ClienteRemoto::detener_cliente() {
	parar();
	cliente->desconectar();
}

ClienteRemoto::ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons, ConsultasClientesServidor& cons):
	cliente(cl), blresolvedor(rcons), cs(cons) {
}

ClienteRemoto::~ClienteRemoto() {
	detener_cliente();
	delete cliente;
}
