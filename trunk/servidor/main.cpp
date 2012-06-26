#include <iostream>
#include <string>
#include "servidor/Servidor.h"
#include "../comun/Definiciones.h"
#include "ArchivoConfiguracion.h"
#include <sstream>
#include <csignal>


#define RUTACONFIGSERV "servidor.conf"
#define PUERTOCLIENTE "puerto_cliente"
#define PUERTOAGENTE "puerto_agente"
#define DEFAULTAGENTE 4321
#define DEFAULTCLIENTE 12345

template <class T, class Y> 
void convertir(T& objetivo, Y& destino) {
	stringstream st;
	st << objetivo;
	st >> destino;
}

int main(int argc, char **argv) {
	std::string aux = RUTACONFIGSERV;
	ArchivoConfiguracion archivo(aux.c_str());
	aux = PUERTOCLIENTE;
	std::string scliente = archivo.obtenerAtributo(aux);
	aux = PUERTOAGENTE;
	std::string sagente = archivo.obtenerAtributo(aux);
	Puerto cliente = DEFAULTCLIENTE, agente = DEFAULTAGENTE;
	convertir(scliente, cliente);
	convertir(sagente, agente);
	Servidor serv(cliente, agente);
	if (!serv.funcional()) {
		std::cout << "puertos elegidos en uso, por favor espere 2 minutos e intente nuevamente" << std::endl;
		return 1;
	}
	std::string a("");
	std::string q("q");
	while (a != q) {
		std::cout << "ingrese 'q' para salir: ";
		std::cin >> a;
		std::cout << std::endl;
	}
	return 0;
}

