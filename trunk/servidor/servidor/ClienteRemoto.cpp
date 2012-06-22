#include "ClienteRemoto.h"
#include <iostream>

void ClienteRemoto::correr() {
	while (corriendo()) {
		if (cliente && cliente->conectado()) {
			ConsultaClienteServidor parConsulta;
			parConsulta.first = this;
			if (cliente->recibir(parConsulta.second)) {
				std::cout << "CLIENTE REMOTO:recibi consulta para " << parConsulta.second.devolverID() << std::endl;
				std::cout << "CLIENTE REMOTO:serializacion = " << parConsulta.second.serializar() << std::endl;
				cs.push(parConsulta);
			}
			else {
				std::cout << "CLIENTE REMOTO:fallo la recepcion, estoy por detener el cliente remoto" << std::endl;
				parar();
			}
		} else {
			std::cout << "CLIENTE REMOTO:no tengo socket o no esta conectado, ergo se cerro" << std::endl;
			parar();
		}
	}
}

void ClienteRemoto::enviarRespuesta(Respuesta& r) {
    Lock l(m);
	if (cliente && cliente->conectado()) {
	    std::cout << "CLIENTE REMOTO:Antes de enviar la respuesta, serialización: " << r.serializar() << std::endl;
		if (!cliente->enviar(r)) {
			std::cout << "CLIENTE REMOTO:fallo el envio, estoy por detener el cliente remoto" << std::endl;
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
