/*
 * Main.cpp
 *
 *  Created on: 29/05/2012
 *      Author: migue
 */

#include <iostream>
#include "ArchivoConfiguracion.h"
#include "Pruebas.h"
#include "pruebaSocket.h"
#include "PruebaCCS.h"
#include "PruebaSS.h"

using namespace std;

int main() {
	testSeparador();
	testIndice();
	testConsulta();
	testRespuesta();
	testMFechas();
	testIndFechas();
	testOrganizacion();
	testArchivoDeDatos();
	testInterseccion();
	testBaseDeDatos();
	testValidadorEntrada();

	testValidadorConsulta();
	testPesadoSeparador();
	testSS();
	testSocket();
	testCCS();



	testBaseDeDatosReal();


	testGeneradorRegistros();

	char ruta[] = "configuracionprueba";
	ArchivoConfiguracion archivo(ruta);
	ArchivoConfiguracion::iterator iter;
	for (iter = archivo.begin(); iter != archivo.end(); ++iter) {
		cout << "atributo: " << iter->first << " valor = " << iter->second << endl;
	}
	return 0;
}

