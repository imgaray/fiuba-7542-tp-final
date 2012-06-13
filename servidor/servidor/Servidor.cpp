#include "Servidor.h"
#include <iostream>
#include <fstream>
#include "Organizacion.h"
#define RSERVIDOR "servidor.config"
using namespace std;

Respuesta Servidor::resolverEntrada(Consulta& entrada) {
	if (vde.verificarEntrada(entrada)) {
		return bdd->agregarEntrada(entrada);
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta("ERROR");
}

Respuesta Servidor::resolver(Consulta& consulta) {
	if (vdc.verificarConsulta(consulta)) {
		return bdd->resolverConsulta(consulta);
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta("ERROR");
}

Servidor::Servidor(Puerto cliente, Puerto agente): cds(*this, *this,
													cliente, agente) {
	Organizacion::cargarDefiniciones(RUTA_ARCH_MODELO);
	//generarRegistros(bdd, 1000);

	bdd = new BaseDeDatos("BDD.dat");

	cds.comenzar();
}

Servidor::~Servidor() {
	cds.detener();

	delete bdd;
}
