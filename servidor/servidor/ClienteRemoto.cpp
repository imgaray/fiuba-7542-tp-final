#include "ClienteRemoto.h"

void ClienteRemoto::detener_cliente() {
	parar();
	if (cliente)
		cliente->desconectar();
	//sincronizar();
}

void ClienteRemoto::correr() {
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

ClienteRemoto::ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons):
	cliente(cl), blresolvedor(rcons) {
}

ClienteRemoto::~ClienteRemoto() {
	if (corriendo())
		detener_cliente();
	if (cliente)
		delete cliente;
}
