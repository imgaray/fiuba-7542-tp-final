#include "ClienteRemoto.h"
#include <iostream>

void ClienteRemoto::detener_cliente() {
	parar();
	if (cliente)
		cliente->desconectar();
	sincronizar();
}

void ClienteRemoto::correr() {
	while (corriendo()) {
		Consulta c;
		bool valido = false;
		if (cliente->recibir(c)) {
			std::cout << "recibi consulta; serialización: " << c.serializar() << std::endl;
			Respuesta r = blresolvedor.resolver(c);
			valido = cliente->enviar(r);
			std::cout << "envie respuesta" << std::endl;
			std::cout << "Mensaje interno de la respuesta: " << r.mensajeInterno() << std::endl;
			std::cout << "Serialización de la respuesta: " << r.serializar() << std::endl;
		}
		if (!valido) {
			std::cout << "entro a not valido de correr de cliente remoto, \
			ergo cierra el thread" << std::endl;
			detener_cliente();
		}
	}
}

ClienteRemoto::ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons):
	cliente(cl), blresolvedor(rcons) {
}

ClienteRemoto::~ClienteRemoto() {
	if (corriendo())
		detener_cliente();
	if (cliente)
		delete cliente;
}