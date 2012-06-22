#include "Servidor.h"
#include <iostream>
#include <fstream>
#include "Organizacion.h"
#define RSERVIDOR "servidor.config"
using namespace std;

Respuesta Servidor::resolverEntrada(Consulta& entrada) {
	if (vde.verificarEntrada(entrada)) {
		Respuesta r = bdd->agregarEntrada(entrada);
		r.definirID(entrada.devolverID());
		std::cout << "Respuesta válida: " << r.serializar() << std::endl;
		return r;
	}
	// TODO: al integrar, habria que reformular esto
	return Respuesta("ERROR");
}

Respuesta Servidor::resolver(Consulta& consulta) {
	if (vdc.verificarConsulta(consulta)) {
	   	Respuesta r = bdd->resolverConsulta(consulta);
		r.definirID(consulta.devolverID());
		std::cout << "ID respuesta = " << r.devolverID() << std::endl;
		std::cout << "Respuesta válida: " << r.serializar() << std::endl;
		return r;
	}
	    std::cout << "Consulta NO OK" << std::endl;
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
