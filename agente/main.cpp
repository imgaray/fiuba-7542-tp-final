/*
 * main.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#include <iostream>
#include "Agente.h"


int main(int argc, char** argv) {
	if (argc > 1) {
		Agente agente(argv[0]);
		if (argc > 2) {
			agente.cargarDesdeArchivo(argv[1]);
		}
		else {
			agente.cargarDesdeConsola();
		}
	}
	else {
		std::cout << "Faltan parametros: rura archivo configuracion y/o ruta de archivo de datos."<< std::endl;
	}

	return 0;
}
