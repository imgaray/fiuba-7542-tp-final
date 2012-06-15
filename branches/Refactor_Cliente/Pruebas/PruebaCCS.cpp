/*
 * PruebaCCS.cpp
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */
#include "PruebaCCS.h"
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;


void imprimirRes(const Respuesta& resp) {
	cout << "RESPUESTA." << endl;
	cout << "Mensaje Interno: " << resp.mensajeInterno() << endl;
	cout << "Cantidad Col: " << resp.cantidadColumnas() << endl;
	cout << "Cantidad Fil: " << resp.cantidadFilas() << endl;

	for (unsigned i = 0; i < resp.cantidadFilas() ; i++) {

		for (unsigned j = 0; j < resp.cantidadColumnas() ; j++) {
			cout.width(15);
			cout.fill('.');
			cout << resp.dato(i, j);
			cout << "||";
		}
		cout <<  endl;

	}


	cout << "Fin De REspuesta"<< endl;
	cout << endl;
}


void testCCS() {
	cout << "======================================" << endl;
	cout << "Inicia el Test CCS" << endl;


	string rutaOrganizacion = "./organizacion.txt";
	{
		std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
		std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
		fstream archOrg(rutaOrganizacion.c_str(), fstream::out);


		archOrg << dimensiones;
		archOrg << endl;
		archOrg << hechos;

		archOrg.close();
	}
	cout << "Se cargo la Organizacion" << endl;

	ccsServidor s;
	ccsCliente c;

	s.iniciar();

	sleep(3);

	c.iniciar();

	c.sincronizar();
	s.sincronizar();


	cout << "Fin de Test CCS" << endl;
}
