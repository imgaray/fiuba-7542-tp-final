#include "ClienteRemoto.h"
#include <iostream>

void ClienteRemoto::iniciar() {
	hce.iniciar();
	hcr.iniciar();
	hcrc.iniciar();
}

void ClienteRemoto::detener_cliente() {
	cliente->desconectar();
	cconsultas.close();
	crespuestas.close();
	hce.parar();
	hcr.parar();
	hcrc.parar();
}

ClienteRemoto::ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons):
	cliente(cl), blresolvedor(rcons), hce(cl, crespuestas),
	 hcr(cl, cconsultas), hcrc(cconsultas, crespuestas, rcons) {
}

ClienteRemoto::~ClienteRemoto() {
	detener_cliente();
	hce.sincronizar();
	hcr.sincronizar();
	hcrc.sincronizar();
	delete cliente;
}
