#include "AgenteRemoto.h"

void AgenteRemoto::iniciar() {
	hce.iniciar();
	hcr.iniciar();
	hcre.iniciar();
}

void AgenteRemoto::detener_agente() {
	agente->desconectar();
	cconsultas.close();
	crespuestas.close();
	hce.parar();
	hcr.parar();
	hcre.parar();
}

AgenteRemoto::AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr):
		agente(agt), blresolvedor(rentr), hcr(agt, cconsultas),
		hce(agt, crespuestas), hcre(cconsultas, crespuestas, rentr) {
}

AgenteRemoto::~AgenteRemoto() {
	detener_agente();
	hce.sincronizar();
	hcr.sincronizar();
	hcre.sincronizar();
	delete agente;
}
