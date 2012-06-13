#include "Servidor.h"
#include <iostream>
#include <fstream>
#include "Organizacion.h"
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
	std::string rutaOrganizacion = "./organizacion.txt";
	{

	std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
	std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
	fstream archOrg(rutaOrganizacion.c_str(), fstream::out);


	archOrg << dimensiones;
	archOrg << endl;
	archOrg << hechos;

	archOrg.close();

	}

	Organizacion::cargarDefiniciones(rutaOrganizacion);
	//generarRegistros(bdd, 1000);
	cds.comenzar();
}

Servidor::~Servidor() {
	cds.detener();
}
