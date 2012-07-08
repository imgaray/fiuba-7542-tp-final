/*
 * PruebasAgente.cpp
 *
 *  Created on: 10/06/2012
 *      Author: migue
 */

#include "PruebasAgente.h"
#include "../agente/Agente.h"
#include "../comun/Organizacion.h"
#include "../comun/Utilitario.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

void testAgenteCargaConfig() {
	cout << "=======================================" << endl;
	int errores = 0;
	cout << "Inicia Test para carga de Configuracion del Agente."<< endl;

	string ruta = "./configAgente";
	{
		string c1 = "PUERTO = 4333";
		string c2 = "HUESPED = huespedLocal";

		fstream arch(ruta.c_str(), fstream::out);
		arch << c1;
		arch << std::endl;
		arch << c2;

		arch.close();
	}

	Agente Agente(ruta);


	cout << "Fin de Test para Agente Simple." << endl;
}

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

void testAgenteCargaDesdeArchivo() {
	cout << "=======================================" << endl;
	int errores = 0;
	cout << "Inicia Test para CargaDesdeArchivo de Agente."<< endl;
	Utilitario u;

	string rutaOrganizacion = "./Fuente/org.txt";
	{
		string c1 = "Dimensiones = { Marca, Fecha, Producto, Vendedor}";
		string c2 = "Hechos = { PrecioVenta, PrecioLista }";

		fstream arch(rutaOrganizacion.c_str(), fstream::out);
		arch << c1;
		arch << std::endl;
		arch << c2;

		arch.close();
	}
	Organizacion::cargarDefiniciones(rutaOrganizacion);


	string rutaDatos = "./datosParaAgente.txt";
	{
		int cantReg = 7;
		string reg[] ={
				"Samsung \t 1-11-1223 \t Galaxy \t Gonzalo \t 200 \t 250",
				"Apple \t 2-11-1223 \t Iphone 3G \t Pablo \t 300 \t 350",
				"Samsung \t 3-11-1223 \t Tablet \t Gonzalo \t 500 \t 550",
				"Hitachi \t 4-11-1223 \t Notebook \t Gonzalo \t 400 \t 250",
				"Apple \t 5-11-1223 \t MacOS \t Gonzalo \t 200 \t 250",
				"Sony \t 6-11-1223 \t VAIO \t Gustavo \t 200 \t 250",
				"HP \t 7-11-1223 \t Galaxy \t Sebastia \t 800 \t 250"};

		for (int i = 0; i < cantReg ; i++)
			u.borrarCaracter(reg[i], ' ');


		fstream arch(rutaDatos.c_str(), fstream::out);

		for (int i = 0; i < cantReg ; i++) {
			arch << reg[i];
			arch << '\n';
		}

		arch.close();
	}




	string ruta = "./configAgente";
	{
		string c1 = "PUERTO = ";
		c1 += u.convertirAString(PUERTO_PRUEBA_SERVIDOR);
		string c2 = "HUESPED = localhost";

		fstream arch(ruta.c_str(), fstream::out);
		arch << c1;
		arch << std::endl;
		arch << c2;

		arch.close();
	}

	mServidor servidor;
	servidor.iniciar();

	sleep(3);

	Agente agente(ruta);
	agente.cargarDesdeArchivo(rutaDatos);
	cout << "Todos los datos cargados desde Archivo." << endl;


	servidor.sincronizar();
	cout << "Fin de Test para Agente Simple." << endl;
}
