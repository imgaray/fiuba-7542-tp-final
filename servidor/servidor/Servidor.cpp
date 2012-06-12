#include "Servidor.h"
#include <iostream>
#define RSERVIDOR "servidor.config"
using namespace std;

Respuesta Servidor::resolverEntrada(Consulta& entrada) {
	if (vde.verificarEntrada(entrada)) {
		return bdd.agregarEntrada(entrada);
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta("ERROR");
}

Respuesta Servidor::resolver(Consulta& consulta) {
	if (vdc.verificarConsulta(consulta)) {
		return bdd.resolverConsulta(consulta);
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta("ERROR");
}

Servidor::Servidor(Puerto cliente, Puerto agente): cds(*this, *this,
													cliente, agente) {
	cds.comenzar();
}

Servidor::~Servidor() {
	cds.detener();
}
