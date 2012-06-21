/*
 * main.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#include <iostream>
#include "Agente.h"

#define RUTA_CONFIG "agente.conf"

int main(int argc, char** argv) {
    Agente agente(RUTA_CONFIG);

    if (argc > 1) {
			agente.cargarDesdeArchivo(argv[1]);
		}
    else {
			agente.cargarDesdeConsola();
		}


	return 0;
}
