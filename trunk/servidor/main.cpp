#include <iostream>
#include <string>
#include "servidor/Servidor.h"
#include "../comun/Definiciones.h"
#include "ArchivoConfiguracion.h"
#include <sstream>
#include <csignal>
#include <cstring>

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

bool esPuerto(std::string& verificar) {
	bool ret = true;
	for(int i = 0; i <(int) verificar.size(); ++i) {
		if (!isdigit(verificar[i])) {
			ret = false;
		}
	}
	return ret;
}

bool obtenerPuerto(std::string& puerto) {
	int i = 0;
	do {
		std::getline(std::cin, puerto);
		if (!esPuerto(puerto)) {
			std::cout << "El puerto ingresado no es valido." << std::endl << 
			"Por favor ingrese un numero de puerto: " << std::endl;
		}
		++i;
	} while (!esPuerto(puerto) && i != MAX_INTENTOS);
	return (i != MAX_INTENTOS);
}

int configurar() {
	std::string ruta = RUTACONFIGSERV;
	ArchivoConfiguracion arch(ruta.c_str());
	std::string atr_puerto_agente = PUERTOAGENTE;
	std::string atr_puerto_cliente = PUERTOCLIENTE;

	std::cout << "::::::Modo Configuracion::::::" << std::endl;

	std::string puerto_agente;
	std::cout << "Puerto de Agente actual: ";
	std::cout << arch.obtenerAtributo(atr_puerto_agente) << std::endl;
	std::cout << "1) ingrese el puerto del agente: ";
	if (!obtenerPuerto(puerto_agente)) {
		std::cout << "No se configuraron los puertos." << std::endl;
		return 2;
	}

	std::string puerto_cliente;
	std::cout << std::endl << "Puerto de Cliente actual: ";
	std::cout << arch.obtenerAtributo(atr_puerto_cliente) << std::endl;
	std::cout << "2) ingrese el puerto del cliente: ";
	if (!obtenerPuerto(puerto_cliente)) {
		std::cout << "No se configuraron los puertos." << std::endl;
		return 2;
	}

	if (puerto_agente.empty() && puerto_cliente.empty())
		return 0;

	if (puerto_cliente == puerto_agente) {
		std::cout << "No se puede asignar el mismo puerto para entradas." << std::endl;
		return 2;
	}

	if (puerto_agente.empty() == false)
		arch.setearAtributo(atr_puerto_agente, puerto_agente);

	if (puerto_cliente.empty() == false)
		arch.setearAtributo(atr_puerto_cliente, puerto_cliente);

	if (!puerto_cliente.empty() || !puerto_agente.empty())
	std::cout << "Configuracion realizada correctamente." << std::endl;
	return 0;
}

int main(int argc, char **argv) {

	if (argc > 1) {
		if ((argc == 2) && (strcmp(argv[1], "-c") == 0)) {
			return configurar();
		} else {
			std::cout << "Parametros invalidos. Modo de uso: " << std::endl;
			std::cout << "- ./main -c para entrar en modo configuracion. Luego de configurar, vuelva a ejecutar el servidor." << std::endl;
			std::cout << "- ./main para correr el servidor. Asegurese de tenerlo correctamente configurado." << std::endl;
			return 3;
		}
	}
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

