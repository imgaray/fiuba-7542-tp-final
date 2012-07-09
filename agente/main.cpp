/*
 * main.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#include <iostream>
#include "Agente.h"
#include "Definiciones.h"
#include "ArchivoConfiguracion.h"
#include <cstring>
#include <string>

#define RUTA_CONFIG "agente.conf"
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
	std::string atr_puerto = PUERTO_AGENTE_ATR;
	std::string atr_nombre = HOST_AGENTE_ATR;
	std::string ruta = RUTA_CONFIG;
	ArchivoConfiguracion arch(ruta.c_str());

	std::string puerto;
	std::cout << "Puerto Actual: ";
	std::cout << arch.obtenerAtributo(atr_puerto);
	std::cout << std::endl;
	std::cout << "1) ingrese el puerto del host: ";
	if (!obtenerPuerto(puerto)) {
		std::cout << "No se configuro el agente." << std::endl;
		return 2;
	}

	std::string nombre_host;
	std::cout << std::endl << "Huesped Actual: \""<<  arch.obtenerAtributo(atr_nombre);
	std::cout << "\"" << std::endl;
	std::cout << "2) ingrese el nombre del host: ";
	std::getline(std::cin, nombre_host);


	if (puerto.empty() == false)
		arch.setearAtributo(atr_puerto, puerto);

	if (nombre_host.empty() == false)
		arch.setearAtributo(atr_nombre, nombre_host);

	std::cout << "Configuracion realizada correctamente." << std::endl;
	return 0;
}

int main(int argc, char** argv) {
	if ((argc == 2) && (strcmp(argv[1], "-c") == 0)) {
		return configurar();
	}
    Agente agente(RUTA_CONFIG);
    if (argc > 1) {
		agente.cargarDesdeArchivo(argv[1]);
	}
    else {
		agente.cargarDesdeConsola();
	}
	return 0;
}
