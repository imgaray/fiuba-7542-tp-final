#include "Servidor.h"
#include <iostream>
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

Servidor::Servidor(): cds(*this, *this) {
	cds.comenzar();
}

Servidor::~Servidor() {
	cds.detener();
}
