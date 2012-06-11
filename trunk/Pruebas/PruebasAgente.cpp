/*
 * PruebasAgente.cpp
 *
 *  Created on: 10/06/2012
 *      Author: migue
 */

#include "PruebasAgente.h"
#include "../agente/Agente.h"
#include "../comun/Organizacion.h"
#include <iostream>
#include <fstream>

using namespace std;

void testAgenteSimple() {
	cout << "=======================================" << endl;
	int errores = 0;
	cout << "Inicia Test para Agente Simple."<< endl;

	string ruta = "./Fuente/org.txt";
	{
		string c1 = "Dimensiones = { Marca,  Fecha, Bonificacion, Producto, Vendedor}";
		string c2 = "Hechos = { PrecioVenta ,PrecioLista }";

		fstream arch(ruta.c_str(), fstream::out);
		arch << c1;
		arch << std::endl;
		arch << c2;

		arch.close();
	}
	Organizacion::cargarDefiniciones(ruta);

	Agente agente;

	agente.cargarDesdeConsola();

	cout << "Fin de Test para Agente Simple." << endl;
}
