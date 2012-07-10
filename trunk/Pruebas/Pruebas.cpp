/*
 * Pruebas.cpp
 *
 *  Created on: 03/06/2012
 *      Author: migue
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Pruebas.h"

#include "Organizacion.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "M_Fechas.h"
#include "GenRegistros.h"

#include "BaseDeDatos.h"
#include "VerificadorConsultasH.h"
#include "VerificadorEntradasH.h"
#include "IndiceDeFechas.h"
#include "ArchivoDeDatos.h"

using namespace std;

void eliminarArchivo(const std::string& ruta) {
	std::string comando = "rm ";
	comando += ruta;
	system(comando.c_str());
}

void crearOrganizacionEstandar(const std::string& ruta) {
	string c1 = "Dimensiones = { Sucursal, Vendedor, Fecha, Marca, Producto}";
	string c2 = "Hechos = { PrecioLista, PrecioVenta }";

	std::fstream arch(ruta.c_str(), fstream::out);
	arch << c1;
	arch << std::endl;
	arch << c2;

	arch.close();
}

void imprimirRespuesta(Respuesta& resp, const string& comentario) {
	cout << endl;
	cout << "Comentario: " << comentario << endl;
	cout << "Estado Resp: " << resp.mensajeInterno() << endl;
	cout << "Cantidad Filas: " << resp.cantidadFilas() << endl;
	cout << "Cantidad Columnas: " << resp.cantidadColumnas() << endl;
	cout << "Datos Recibidos:" << endl;
	for (unsigned i = 0; i < resp.cantidadFilas() ; i++)  {
		cout << "::";
		for (unsigned j = 0 ; j < resp.cantidadColumnas() ; j++) {
			cout.width(14);
			cout.fill('.');
			cout<< resp.dato(i,j) << "|";
		}
		cout << endl;
	}
}

void testBaseDeDatosReal() {
	cout << "================================================="<< endl;
	cout << "Inicia Test para BaseDeDatos \"Real\"" << endl;


	std::string rutaOrganizacion;
	std::string rutaBDD,rutaBDD_id;

	rutaBDD = "./BDD.dat";
	rutaBDD_id = rutaBDD + "-id.dat";
	rutaOrganizacion = "./organizacion.txt";
	crearOrganizacionEstandar(rutaOrganizacion);

	Organizacion::cargarDefiniciones(rutaOrganizacion);
	BaseDeDatos bdd(rutaBDD);
	generarRegistros(bdd, 1000);


	Consulta c;
	Respuesta r;

	c.agregarEntrada("Producto", "Galaxy SII");
	c.agregarEntrada("Sucursal", "Avellaneda");

	c.agregarResultado("Vendedor");
	c.defininirAgregacion(CONT, "PrecioVenta");

	VerificadorConsultasH verif;

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 1" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Consulta 2");

	// Segunda Consulta
	c.limpiar();

	c.agregarEntrada("Sucursal", "San Miguel");
	c.agregarEntrada("Vendedor", "Juan");
	c.agregarFiltro("Producto", "Galaxy SII");

	c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 2" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Primer COnsulta Verdadera");

	// Tercera Consulta

	c.limpiar();

	c.agregarEntrada("Sucursal", "Avellaneda");
	c.agregarEntrada("Vendedor", "Juan");
	c.agregarFiltro("PrecioLista", ">500");

	c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 3" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Primer COnsulta Verdadera");


	// Cuarta Consulta

	c.limpiar();

	c.agregarEntrada("PrecioLista", "=500");

	c.agregarResultado("Marca");
	c.agregarResultado("Vendedor");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 2" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Cuarta Consulta Verdadera");

	// Consulta de Vendedores
	c.limpiar();

	c.agregarResultado("Vendedor");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida" << endl;
		exit(0);
	}


	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Vendedores");
	// Quinta Consulta

	c.limpiar();

	c.agregarEntrada("Sucursal", "San Salvador");
	//c.agregarEntrada("Vendedor", "Juan");
	c.agregarFiltro("PrecioLista", "<100");

	c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");
	c.agregarResultado("Vendedor");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 5" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Primer COnsulta Verdadera");


	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Primer COnsulta Verdadera");



	// Primer Tabla Pivote

	c.limpiar();
	c.definirConsultaDeTablaPivote();

	c.agregarEntrada("Sucursal", "San Miguel");
	//c.agregarFiltro("Producto", "Galaxy SII");

	c.agregarXTablaP("Vendedor");
	c.agregarYTablaP("Marca");

	//c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 2" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Primer COnsulta Verdadera");

	// Segunda Tabla Pivote


	c.limpiar();
	c.definirConsultaDeTablaPivote();

	c.agregarEntrada("Sucursal", "Avellaneda");
	//c.agregarFiltro("Producto", "Galaxy SII");

	c.agregarXTablaP("Vendedor");
	//c.agregarXTablaP("Fecha");
	c.agregarYTablaP("Marca");
	c.agregarYTablaP("Producto");

	//c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta Invalida 2" << endl;
		exit(0);
	}

	r = bdd.resolverConsulta(c);

	imprimirRespuesta(r, "Segunda Tabla Pivote Verdadera");



	// Consulta de un Registro


	c.limpiar();

	c.agregarEntrada("Vendedor", "Evelyn Magaly");
	c.agregarEntrada("Sucursal", "San Nicolas");

	c.agregarResultado("Vendedor");
	c.agregarResultado("Marca");
	c.defininirAgregacion(CONT, "PrecioLista");

	if (!verif.verificarConsulta(c)) {
		cout << "Consulta de Evelyn Invalida " << endl;
		exit(0);
	}


	r = bdd.resolverConsulta(c);

	r.deserializar(r.serializar());

	imprimirRespuesta(r, "Consulta de Evelyn");

	cout << "Fin de Test de BaseDeDatos Real."<< endl;

	//elimino los archivos utilizados para la prueba
	eliminarArchivo(rutaBDD);
	eliminarArchivo(rutaBDD_id);
	eliminarArchivo(rutaOrganizacion);
}

void testOrganizacion() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl <<"Inicia Test Para Organizacion" << endl;

	string ruta = "./org.txt";
	string c1 = "Dimensiones = { Marca,  Fecha, Bonificacion, Producto, Vendedor,HOGAR, Organizacion}";
	string c2 = "Hechos = { Precio, PrecioVenta ,PrecioLista }";

	std::fstream arch(ruta.c_str(), fstream::out);
	arch << c1;
	arch << std::endl;
	arch << c2;

	arch.close();


	Organizacion::cargarDefiniciones(ruta);

	if (Organizacion::cantidadDimensionesTotal() != 7) {
		errores++;
		cout << "Error en la cantidad de Dimensiones Totales" << endl;
	}

	if (Organizacion::cantidadHechos() != 3) {
		errores++;
		cout << "Error en la cantidad de Dimensiones" << endl;
	}

	cout <<"Muestra de Dimensiones"<< endl;
	for (unsigned i = 0 ; i < Organizacion::cantidadDimensionesTotal() ; i++) {
		cout << "Ind: " << i << " Dim: \"" <<Organizacion::nombreDimension(i) << "\"" <<endl;
	}

	cout << endl << "Muestra de Dimensiones Simples"<< endl;
	for (unsigned i = 0 ; i < Organizacion::cantidadDimensionesSimples() ; i++) {
		cout << "Ind: " << i << " Dim: \"" <<Organizacion::nombreDimensionSimple(i) << "\"" <<endl;
	}


	cout << endl << "Muestra de Hechos"<< endl;
	for (unsigned i = 0 ; i < Organizacion::cantidadHechos() ; i++) {
		cout << "Ind: " << i << " Hecho: \"" <<Organizacion::nombreHecho(i) << "\"" << endl;
	}

	cout << endl << "Muestra de todos los Campos" << endl;
	for (unsigned i = 0; i < Organizacion::cantidadCampos() ; i++) {
		cout << "Ind: " << i << " Campo: " << Organizacion::nombreCampo(i)<< endl;
	}

	cout << endl << "Muestra de todos los Campos simple" << endl;
	for (unsigned i = 0; i < Organizacion::cantidadCamposSimples() ; i++) {
		cout << "Ind: " << i << " Campo: " << Organizacion::nombreCampoSimple(i)<< endl;
	}

	if (!Organizacion::esDimension("Marca")) {
		errores++;
		cout << "Error en esDimension con \"Marca\"" << endl;
	}

	if (!Organizacion::esHecho("Precio")) {
		errores++;
		cout << "Error en esHecho con \"Precio\"" << endl;
	}

	if (Organizacion::indiceDeCampo("Bonificacion") != 2) {
		errores++;
		cout << "Error en indiceDeCampo con \"Bonificacion\"" << endl;
	}

	if (Organizacion::indiceDeCampo("PrecioLista") != 9) {
		cout << endl << "Error en indiceDeCampo con \"PrecioLista\"" << endl;
		cout << "Rec: "<<Organizacion::indiceDeCampo("PrecioLista") << endl;
		cout << "Esp: "<< 7 << endl;
		errores++;
	}

	for (unsigned i = 0; i < Organizacion::cantidadCampos() ; i++) {
		if (Organizacion::indiceDeCampo(Organizacion::nombreCampo(i)) != i) {
			cout << endl << "Error en el calculo de los indices para los campos" << endl;
			errores++;
			cout << "Esp: " <<i << endl;
			cout << "Rec: " <<Organizacion::indiceDeCampo(Organizacion::nombreCampo(i)) << endl;
			cout << "Nombre: "<< Organizacion::nombreCampo(i)<< endl;
		}
	}

	if (Organizacion::cantidadCamposSimples() != (Organizacion::cantidadCampos() -1)) {
		cout << endl << "Error en la cantidad de campos simples" << endl;
		errores++;
	}

	for (unsigned i = 0; i < Organizacion::cantidadCamposSimples() ; i++) {
		if (Organizacion::indiceDeCampoSimple(Organizacion::nombreCampoSimple(i)) != i) {
			cout << endl << "Error en el calculo de los indices para los campos simples" << endl;
			errores++;
			cout << "Esp: " <<i << endl;
			cout << "Rec: " <<Organizacion::indiceDeCampoSimple(Organizacion::nombreCampoSimple(i)) << endl;
			cout << "Nombre: "<< Organizacion::nombreCampoSimple(i)<< endl;
		}
	}

	if (errores == 0) {
		cout << "TEST SIN ERRORES++" << endl << endl;
	}
	else {
		cout << "Errores en Test de Organizacion: "<< errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE Organizacion." << endl;
	eliminarArchivo(ruta);
}


void testValidadorConsulta() {
	cout << "=================================================" << endl;
	cout << "Inicia el Test para el Verificador de Consulta."<< endl;

	// Creo y configuro la organizacion.
	string rutaOrganizacion = "./organizacion.txt";
	{
		string dimensiones = "Dimensiones = { Sucursal, Vendedor, Producto}";
		string hechos = "Hechos = {PrecioLista, PrecioFinal}";
		fstream archOrg(rutaOrganizacion.c_str(), fstream::out);

		archOrg << dimensiones;
		archOrg << endl;
		archOrg << hechos;

		archOrg.close();
	}
	Organizacion::cargarDefiniciones(rutaOrganizacion);



	VerificadorConsultasH vCons;

	int errores = 0;
	Consulta c;

	c.agregarResultado(Organizacion::nombreCampo(0));
	c.agregarResultado(Organizacion::nombreCampo(1));

	if (vCons.verificarConsulta(c) == false) {
		errores++;
		cout << "Error en consulta simple" << endl;
	}


	c.limpiar();

	c.agregarFiltro(Organizacion::nombreCampo(2), "valorF");
	c.agregarFiltro(Organizacion::nombreCampo(1), "valorF2");
	c.agregarResultado(Organizacion::nombreCampo(4));

	if (vCons.verificarConsulta(c) == false) {
		errores++;
		cout << "Error en consulta simple con filtros" << endl;
	}


	c.limpiar();

	c.agregarResultado("ALALA");
	c.agregarResultado("alala");

	if (vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al aprobar consulta erronea" << endl;
	}


	c.limpiar();
	c.agregarFiltro("asdads", "asdasd");
	c.agregarFiltro("a1", "dasd");
	c.agregarResultado(Organizacion::nombreCampo(2));

	if (vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al aprobar consulta con filtros mal."<< endl;
	}


	c.limpiar();
	c.definirConsultaDeTablaPivote();
	c.defininirAgregacion(PROM, Organizacion::nombreHecho(0));
	c.agregarXTablaP(Organizacion::nombreCampo(0));
	c.agregarYTablaP(Organizacion::nombreCampo(1));

	if (!vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al no aprobar consulta simple de Tabla Pivote." << endl;
	}

	c.limpiar();
	c.definirConsultaDeTablaPivote();
	c.defininirAgregacion(NADA, Organizacion::nombreHecho(0));
	c.agregarXTablaP(Organizacion::nombreCampo(0));
	c.agregarYTablaP(Organizacion::nombreCampo(1));

	if (vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al aprobar consulta simple de Tabla Pivote." << endl;
	}


	c.limpiar();
	c.definirConsultaDeTablaPivote();
	c.defininirAgregacion(NADA, Organizacion::nombreHecho(0));
	c.agregarXTablaP(Organizacion::nombreCampo(0));
	//c.agregarYTablaP(Organizacion::nombreCampo(1));

	if (vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al aprobar consulta simple de Tabla Pivote." << endl;
	}



	c.limpiar();
	c.definirConsultaDeTablaPivote();
	c.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
	c.agregarXTablaP("LALAL");
	c.agregarYTablaP("LALALA");

	if (vCons.verificarConsulta(c)) {
		errores++;
		cout << "Error al aprobar consulta simple de Tabla Pivote." << endl;
	}



	if (errores == 0) {
		cout << "TEST SIN ERRORES++" << endl << endl;
	}
	else {
		cout << "Errores en Test de Verificador de Consulta: "<< errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE Verificador de Consulta." << endl;
	eliminarArchivo(rutaOrganizacion);
}


void testArchivoDeDatos() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl << "Inicia Test para ArchivoDeDatos" << endl;

	std::string rutaArchDatos = "archDatos.txt";
	std::string rutaArchId = (rutaArchDatos + "-id.dat");

	ArchivoDeDatos arch(rutaArchDatos);
	arch.borrarDatos();

	size_t regIniciales = arch.cantidadRegistros();

	string reg1 = "HOLA A TODOS";
	string reg2 = "COMO VA TODO";
	string reg3 = "TODo BIEN";
	string reg4 = "ESTA SALIENDO EL SOL\n";
	string reg5 = "HOY ME SIENTO BIEN!!!";
	string reg6 = "NO PERDI LA FE!!!";

	arch.guardarRegistro(reg1);
	arch.guardarRegistro(reg2);
	arch.guardarRegistro(reg3);
	arch.guardarRegistro(reg4);
	arch.guardarRegistro(reg5);
	arch.guardarRegistro(reg6);

	if (arch.cantidadRegistros() != (regIniciales + 6)) {
		cout << "Error en la cantidad de Registros" << endl;
		cout << "Esp: "<< 6 << endl;
		cout << "Rec: "<< dec << arch.cantidadRegistros() << endl;
		errores++;
	}


	string regRecuperado;

	regRecuperado = arch.obtenerRegistro(1);

	if (regRecuperado != reg2) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg2 << endl;
		errores++;
	}

	regRecuperado = arch.obtenerRegistro(4);

	if (regRecuperado != reg5) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg5 << endl;
		errores++;
	}

	regRecuperado = arch.obtenerRegistro(0);

	if (regRecuperado != reg1) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg1 << endl;
		errores++;
	}


	regRecuperado = arch.obtenerRegistro(3);

	if (regRecuperado != reg4) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg4 << endl;
		errores++;
	}

	regRecuperado = arch.obtenerRegistro(1);

	if (regRecuperado != reg2) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg2 << endl;
		errores++;
	}

	regRecuperado = arch.obtenerRegistro(5);

	if (regRecuperado != reg6) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << reg6 << endl;
		errores++;
	}

	string regNuevo = "REGISTRO NUEVO";

	arch.guardarRegistro(regNuevo);
	regRecuperado = arch.obtenerRegistro(arch.cantidadRegistros() - 1);

	if (regRecuperado != regNuevo) {
		cout << "Error en registro recuperado" << endl;
		cout << "Rec: " << regRecuperado << endl;
		cout << "Esp: " << regNuevo << endl;
		errores++;
	}


	if (errores == 0) {
		cout << "Test SIN ERRORES++" << endl;
	}
	else {
		cout << "Test Con errores: "<< errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE ARCHIVODEDATOS" << endl;
	eliminarArchivo(rutaArchDatos);
	eliminarArchivo(rutaArchId);
}


void testInterseccion() {
	cout << "=================================================" << endl;
	cout << "Inicia test para Interseccion" << endl;
	int errores = 0;

	std::string rutaBDD = "ruta.txt";
	std::string rutaBDDid(rutaBDD + "-id.dat");

	BaseDeDatos bdd(rutaBDD);

	Lista_Id l1;
	Lista_Id l2;

	l1.push_back(1);l1.push_back(3);l1.push_back(5);l1.push_back(6);
	l1.push_back(7);l1.push_back(9);l1.push_back(10);l1.push_back(11);
	l1.push_back(14);

	l2.push_back(0);l2.push_back(3);l2.push_back(5);l2.push_back(8);
	l2.push_back(9);l2.push_back(11);l2.push_back(12);l2.push_back(13);
	l2.push_back(14);l2.push_back(15);

	Lista_Id interseccion;

	bdd.calcularInterseccion(l1,l2,interseccion);

	Lista_Id::const_iterator it;

	cout << endl;

	cout << "Intersecciones: " << endl;
	for (it = interseccion.begin() ; it!=interseccion.end() ; ++it) {
		cout << "valor: " << dec << *it << endl;
	}


	if (errores == 0) {
		cout << endl << "Test Sin Errores++" << endl;
	}
	else {
		cout << "Errores en test:" << errores << endl;
		exit(0);
	}

	cout << "Fin de test de BaseDeDatos::Interseccion" << endl;

	eliminarArchivo(rutaBDD);
	eliminarArchivo(rutaBDDid);
}


void testBaseDeDatos() {
	cout << "=================================================" << endl;
	cout << endl << "Inicia el Test para BaseDeDatos." << endl;
	int errores = 0;

	M_Fechas mf;


	// Creo y configuro la organizacion.
	string rutaOrganizacion = "./organizacion.txt";
//	{
//
//	std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
//	std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
//	fstream archOrg(rutaOrganizacion.c_str(), fstream::out);
//
//
//	archOrg << dimensiones;
//	archOrg << endl;
//	archOrg << hechos;
//
//	archOrg.close();
//
//	}
	crearOrganizacionEstandar(rutaOrganizacion);

	Organizacion::cargarDefiniciones(rutaOrganizacion);

	string rutaDatos = "./datos-bdd.txt";
	string rutaDatosId = rutaDatos + "-id.dat";

	BaseDeDatos bdd(rutaDatos);
	bdd.borrarDatos();
	cout << "Se creo la base de datos" << endl;

	string reg1[] = {"Avellaneda","Santiago",	"12-12-2012","Samsung Galaxy","500","600"};
	string reg2[] = {"Lomas",	"Miguel",		"12-12-2012","Samsung Galaxy","600","1600"};
	string reg3[] = {"Lomas",	"Pablo",		"12-11-2012","Samsung Tablet","150","1000"};
	string reg4[] = {"Avellaneda","Gustavo",	"12-10-2011","Samsung e-215","550","660"};
	string reg5[] = {"Avellaneda",	"Pablo",	"12-08-2012","Samsung Tablet","600","650"};
	string reg6[] = {"San Martin",	"Pablo",	"11-09-2012","Samsung Tablet","200","850"};
	string reg7[] = {"San Justo",	"Santiago",	"11-09-2012","Samsung Galaxy","140","350"};
	string reg8[] = {"San Martin",	"Pablo",	"11-09-2012","Samsung XP","120","380"};


	int cantReg = 8;

	string **registros;
	registros = new string*[cantReg];
	registros[0] = reg1; registros[1] = reg2; registros[2] = reg3; registros[3] = reg4;
	registros[4] = reg5; registros[5] = reg6; registros[6] = reg7; registros[7] = reg8;

	Consulta cAgente;

	for (int i = 0; i < cantReg ; i++) {
		cAgente.limpiar();
		cAgente.definirComoConsultaAgente();

		for (unsigned j = 0; j < Organizacion::cantidadCampos() ; j++) {
			cAgente.agregarCampo(registros[i][j]);
		}

		bdd.agregarEntrada(cAgente);
		cout << "Reg " << i << " guardado." << endl;
	}

	delete[] registros;


	/*
	 * Comienzan los Consulta por parte de un Cliente
	 */


	Consulta cCliente;
	Respuesta resp;

	cCliente.agregarFiltro(Organizacion::nombreCampo(1),"Pablo");
	cCliente.agregarFiltro(Organizacion::nombreCampo(0),"Lomas");
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.agregarResultado(Organizacion::nombreDimension(0));
	cCliente.defininirAgregacion(SUM,Organizacion::nombreHecho(1));

	resp = bdd.resolverConsulta(cCliente);

	cout << "Respuesta con 2 filtros ( Pablo, Lomas )." << endl;
	cout << "Cantidad Filas: " << resp.cantidadFilas() << endl;
	cout << "Cantidad Columnas: " << resp.cantidadColumnas() << endl;
	cout << "Datos Recibidos:" << endl;
	for (unsigned i = 0; i < resp.cantidadFilas() ; i++)  {
		cout << "::";
		for (unsigned j = 0 ; j < resp.cantidadColumnas() ; j++) {
			cout.width(11);
			cout.fill('.');
			cout<< resp.dato(i,j) << "|";
		}
		cout << endl;
	}

	// segunda Consulta
	cCliente.limpiar();
	cCliente.agregarFiltro(Organizacion::nombreCampo(1),"Pablo");
	cCliente.agregarFiltro(Organizacion::nombreCampo(0),"Lomas");
	cCliente.agregarResultado(Organizacion::nombreCampo(1));

	cCliente.agregarResultado(Organizacion::nombreDimension(0));
	cCliente.agregarFiltro(Organizacion::nombreHecho(1),"<700");
	cCliente.defininirAgregacion(SUM,Organizacion::nombreHecho(1));


	resp = bdd.resolverConsulta(cCliente);
	imprimirRespuesta(resp, "Respuesta con 3 filtros ( Pablo, Lomas, Precio > 900 ).");


	// Segunda Consulta...
	cCliente.limpiar();
	cCliente.agregarResultado(Organizacion::nombreCampo(1));

	resp = bdd.resolverConsulta(cCliente);
	imprimirRespuesta(resp, "Vendedores");



	// Tercer Consulta...
	cCliente.limpiar();
	cCliente.agregarResultado(Organizacion::nombreCampo(0));

	resp = bdd.resolverConsulta(cCliente);
	imprimirRespuesta(resp, "Sucursales");


	cCliente.limpiar();
	cCliente.agregarEntrada(Organizacion::nombreHecho(0),">100");
	//cCliente.defininirAgregacion(SUM, Organizacion::nombreCampo(1));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(MIN, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Entrada: PrecioLista MIN >100. Vendedor");


	cCliente.limpiar();
	cCliente.agregarEntrada(Organizacion::nombreHecho(0),"<300");
	//cCliente.defininirAgregacion(SUM, Organizacion::nombreCampo(1));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(MIN, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Entrada: PrecioLista MIN <300. Vendedor");


	cCliente.limpiar();
	cCliente.agregarFiltro("Fecha", mf.anio("2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.agregarResultado("Fecha");
	cCliente.agregarResultado("Producto");
	//cCliente.defininirAgregacion(MIN, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Entrada: anio 2009. Vendedor, Fecha, Producto");


	cCliente.limpiar();
	//cCliente.agregarEntrada(Organizacion::nombreHecho(0),"<300");
	//cCliente.defininirAgregacion(SUM, Organizacion::nombreCampo(1));
	cCliente.agregarFiltro("Fecha", mf.mes(9,"2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Vendedor y cantidad que vendio del mes 9.");



	cCliente.limpiar();
	cCliente.agregarFiltro("Fecha", mf.bimestre(6,"2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Vendedor y cantidad que vendio del 6to bimestre.");


	cCliente.limpiar();
	cCliente.agregarFiltro("Fecha", mf.mes(10,"2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Vendedor y cantidad que vendio el mes 10.");


	cCliente.limpiar();
	cCliente.agregarFiltro("Fecha", mf.mes(9,"2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Vendedor y cantidad que vendio el mes 9.");



	cCliente.limpiar();
	cCliente.agregarFiltro("Vendedor", "Pablo");
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(PROM, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Promedio que vendio Pablo.");


	cCliente.limpiar();
	cCliente.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Suma de los PrecioDeLista sin filtrado");


	cCliente.limpiar();
	cCliente.defininirAgregacion(NADA, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Todos de los PrecioDeLista sin filtrado");


	cCliente.limpiar();
	cCliente.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
	cCliente.defininirAgregacion(NADA, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Todos de los PrecioDeLista y  PrecioDeVenta");



	cCliente.limpiar();
	cCliente.defininirAgregacion(MIN, Organizacion::nombreHecho(0));
	cCliente.defininirAgregacion(MAX, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Min de PrecioDeLista y  Max de PrecioDeVenta");


	cCliente.limpiar();
	cCliente.agregarFiltro("Fecha", mf.mes(9, "2012"));
	cCliente.defininirAgregacion(MIN, Organizacion::nombreHecho(0));
	cCliente.defininirAgregacion(MAX, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Min de PrecioDeLista y  Max de PrecioDeVenta del mes 9");



	cCliente.limpiar();
	cCliente.agregarEntrada("Fecha", mf.mes(9, "2012"));
	cCliente.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
	cCliente.defininirAgregacion(NADA, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Todos de los PrecioDeLista y  PrecioDeVenta del mes 9.");


	cCliente.limpiar();
	cCliente.agregarEntrada("Vendedor", "Pablo");
	cCliente.agregarEntrada("Fecha", mf.mes(9,"2012"));
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(PROM, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Promedio que vendio Pablo el mes 9.");


	cCliente.limpiar();
	cCliente.agregarEntrada("Vendedor", "Pablo");
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(MAX, Organizacion::nombreHecho(0));
	cCliente.agregarResultado("Producto");
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Maximo para que el PrecioDeLista que vendio Pablo");


	cCliente.limpiar();
	cCliente.agregarEntrada("Vendedor", "Pablo");
	cCliente.agregarResultado(Organizacion::nombreCampo(1));
	cCliente.defininirAgregacion(MAX, Organizacion::nombreHecho(1));
	cCliente.agregarResultado("Producto");
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Maximo para que el PrecioDeVenta que vendio Pablo");



	cout << "Consultas de Tabla Pivote " << endl;

	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarYTablaP("Producto");
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor; Y:Producto ; Res:(CONT) PrecioLista");


	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarYTablaP("Producto");
	cCliente.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor; Y:Producto ; Res:(SUM) PrecioLista");




	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarFiltro("Fecha", mf.mes(9, "2012"));
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarYTablaP("Producto");
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor; Y:Producto ; Res: (CONT)PrecioLista del mes 9");



	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarYTablaP("Sucursal");
	cCliente.agregarYTablaP("Producto");
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor; Y:Producto, Sucursal ; Res: (CONT)PrecioLista.");



	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarXTablaP(Organizacion::nombreHecho(1));
	cCliente.agregarYTablaP("Producto");
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor, PrecioFinal; Y:Producto ; Res: (CONT)PrecioLista.");



	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarXTablaP(Organizacion::nombreHecho(1));
	cCliente.agregarYTablaP("Producto");
	cCliente.agregarYTablaP("Sucursal");
	cCliente.defininirAgregacion(CONT, Organizacion::nombreHecho(0));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor, PrecioFinal; Y:Producto ; Res: (CONT)PrecioLista.");




	cCliente.limpiar();
	cCliente.definirConsultaDeTablaPivote();
	cCliente.agregarXTablaP("Vendedor");
	cCliente.agregarYTablaP("Sucursal");
	cCliente.defininirAgregacion(PROM, Organizacion::nombreHecho(1));
	resp = bdd.resolverConsulta(cCliente);

	imprimirRespuesta(resp, "Tabla Pivote. X: Vendedor; Y:Sucursal ; Res: (PROM)PrecioVenta.");




	cout << endl;
	if (errores == 0) {
		cout << "Test sin Errores++" << endl;
	}
	else {
		cout << "Errores en test:" << errores << endl;
		exit(0);
	}

	cout << "Fin de Test de BaseDeDatos" << endl;


	//elimino los archivo utilizados en el test
	eliminarArchivo(rutaDatos);
	eliminarArchivo(rutaDatosId);
	eliminarArchivo(rutaOrganizacion);
}

void testGeneradorRegistros() {
	// Creo y configuro la organizacion.
	string rutaOrganizacion = "./organizacion.txt";
//	{
//
//	std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
//	std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
//	fstream archOrg(rutaOrganizacion.c_str(), fstream::out);
//
//
//	archOrg << dimensiones;
//	archOrg << endl;
//	archOrg << hechos;
//
//	archOrg.close();
//
//	}

	crearOrganizacionEstandar(rutaOrganizacion);
	Organizacion::cargarDefiniciones(rutaOrganizacion);

	cout << "====================================================" << endl;
	cout << "Inicia el Test de Generador De Registros." << endl;


	string rutaDatos = "./datosRegGen.dat";
	string rutaDatosId(rutaDatos + "-id.dat");
	BaseDeDatos bdd(rutaDatos);

	long cantReg = 50;

	generarRegistros(bdd, cantReg);

	//for (Id_Registro id = 0 ; i <)


	cout << "FIN DE TEST DE Generador de Registros." << endl;

	//elimino los archivos utilizados
	eliminarArchivo(rutaDatos);
	eliminarArchivo(rutaDatosId);
	eliminarArchivo(rutaOrganizacion);

}

void testPesadoSeparador() {
	cout << "========================================" << endl;
	int errores = 0;
	cout << "Inicia Test Pesado para el Separador" << endl;

	char sep = '-';
	string aSeparar = "AAA-BBBB-CCCCC";

	Utilitario util;



	if (util.separar(aSeparar, sep, 0) != "AAA") {
		cout << "Error en AAA." << endl;
		errores++;
	}


	if (util.separar(aSeparar, sep, 1) != "BBBB") {
		cout << "Error en BBBB" << endl;
		errores++;
	}


	if (util.separar(aSeparar, sep, 2) != "CCCCC") {
		cout << "Error en CCCCC"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 3) != "") {
		cout << "Error en retorna argmento vacio" << endl;
		errores++;
	}



	aSeparar = "ASVAVABAVASC";

	if (util.separar(aSeparar, sep, 0) != aSeparar) {
		cout << "Error al no retornar el string Base."<< endl;
	}


	if (util.separar(aSeparar, sep, 1)  != "") {
		cout << "Error en retono de argumento vacio 2";
		errores++;
	}


	aSeparar = "-aaa-bbb-ccc--";

	if (util.separar(aSeparar, sep, 0) != "") {
		cout << "Error en retorno de argumento vacio 3" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 1) != "aaa") {
		cout << "Error en retorno mal de argumento aaa" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 2) != "bbb") {
		cout << "Error en retrono mal de argumentos bbb" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 3) != "ccc") {
		cout << "Error en retorno mal de argumento ccc" << endl;
	}

	if (util.separar(aSeparar, sep, 4) != "") {
		cout << "Error en retorno mal de argumento vacio 4" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 5) != "") {
		cout << "Error en retorno mal de argumento vacio 5" << endl;
		errores++;
	}

	string c1 = "askhfdbasvasbcjasvckjas";
	string c2 = "akjsbdasdbfkasbjkcaskjcvasjkc";
	string c3 = "asdkfbaksdbfvsdabckasvcasvkjcas";
	string c4 = "asfsadbvasdvchasvhjadhgcvasvcsajvcsavchjdavgdavcajscvsahgvcsavc";

	aSeparar = c1;
	aSeparar += sep;
	aSeparar += c2;
	aSeparar += sep;
	aSeparar += c3;
	aSeparar += sep;
	aSeparar += c4;


	if (util.separar(aSeparar, sep, 0) != c1) {
		cout << "Error en c1"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 1) != c2) {
		cout << "Error en c2" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 2) != c3) {
		cout << "Error en c3"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 3) != c4) {
		cout << "Error en c4" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 4) != "") {
		cout << "Error en retorna arg vacio 6" << endl;
		errores++;
	}



	aSeparar = "";

	if (util.separar(aSeparar, sep, 0) != "") {
		cout << "Error en dato vacio 1"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 1) != "") {
		cout << "Error en dato vacio 2"<< endl;
		errores++;
	}


	if (util.separar(aSeparar, sep, 4) != "") {
		cout << "Error en dato vacio 3"<< endl;
		errores++;
	}


	if (util.separar("", sep, 0) != "") {
		cout << "Error en dato vacio 4"<< endl;
		errores++;
	}

	if (util.separar("", sep, 1) != "") {
		cout << "Error en dato vacio 3"<< endl;
		errores++;
	}


	if (util.separar("", sep, 4) != "") {
		cout << "Error en dato vacio 5"<< endl;
		errores++;
	}


	aSeparar.clear();

	if (util.separar(aSeparar, sep, 0) != "") {
		cout << "Error en dato vacio 6"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 1) != "") {
		cout << "Error en dato vacio 7"<< endl;
		errores++;
	}


	if (util.separar(aSeparar, sep, 4) != "") {
		cout << "Error en dato vacio 8"<< endl;
		errores++;
	}


	c1 = "alskjflkasjlkasjlkvjaklsvnalksdnclkasnclkasjlkvnalkvnalkndslckanslkdcjalksdvjklaklandklnakl ndaaksdhkashdk"
			"asdkjashckjahsjkchasjlkhcjkasdhkjsdbk bskdjhaljkdn ljkal knalknadln ljadnvcljanldjcnaldnclaknclkansdcla"
			"askjdnasicbaskcbaksncakscnakscnakscnakjscn kajsn kas ascascsaasiduhcasochaa aisuhcaish asncaskjcnaskcjn";


	c2 = "akscoasnckankjnakj nkajdhkahdkcjabkjbakjbafviegwqfihweqoivnuiewqgviwhvisogvaehgcioaehiagcoiugaehic asdcasc"
			"aochaiuchaiechiueashvouahefcoiajioyaeuvyuiohvklznvm,xzc bkgyegc aciauehcoahicyageciuacojmaoi hoaidjasdv"
			"akchaoscjoiadshcui agdiycgauocoaenmoahicuhadui badjbkadb kadb akd baakjcnaknaksjnkajsnckjasnc askcnasak"
			"alkdjcnaidb aidbiaudb ouab obakjsnjcknc,jxzhbbqkbckabckabckjabsckjasdcnaasdascaskcxnasjkcnkajsnaosdjasd";

	c3 = "akjhsbcjab ahkscljanslcknaslkcnalsknhvlkjahvlkahvljkakj bzxkb kwehgfiugauicgaiuscasasdacascac"
			"asdhaskchakshcaushcachasnckjadn kjadn kajdn kjdankjvaijvpiequfoivuqoiv hyiqohvpvhqio asdas"
			"aovaohvaeljc nalknclkajlkchalskhvclahcoqwiycoiashvoxlvjzlkxc mnm,wndkwqdhcoiwquydciwuyasda";


	aSeparar = c1;
	aSeparar += sep;
	aSeparar += c2;
	aSeparar += sep;
	aSeparar += c3;
	aSeparar += sep;


	if (util.separar(aSeparar, sep, 0) != c1) {
		cout << "Error en c1 largo"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 1) != c2) {
		cout << "Error en c2 largo" << endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 2) != c3) {
		cout << "Error en c3 largo"<< endl;
		errores++;
	}

	if (util.separar(aSeparar, sep, 3) != "") {
		cout << "Error en argVacio largo"<< endl;
		errores++;
	}


	if (errores == 0) {
		cout<< "Test sin Errores++"<< endl;
	}
	else {
		cout << "Test con Errores: "<< errores << endl;
		exit(0);
	}

	cout << "Fin de Test Pesado para Separador" << endl;
}


#include <fstream>

typedef size_t ID;

void testSeparador() {
	cout << "=================================================" << endl;
	cout << "Test Para Separador" << endl;

	string c1 = "|ABCD||EFG|HIJKLM|OPQ|";
	char sep = '|';

	Utilitario util;

	string a0 = util.separar(c1, sep, 0);
	cout << "Arg 0: \""<< a0 << "\""<< endl;

	string a1 = util.separar(c1, sep, 1);
	cout << "Arg 1: \""<< a1 << "\""<< endl;

	string a2 = util.separar(c1, sep, 2);
	cout << "Arg 2: \""<< a2 << "\""<< endl;

	string a3 = util.separar(c1, sep, 3);
	cout << "Arg 3: \""<< a3 << "\""<< endl;

	a3 = util.separar(c1, sep, 4);
	cout << "?Arg 4: \""<< a3 <<"\""<< endl;

	cout << "Fin de Test de Separador" << endl;
}

void testIndice() {
	cout << "=================================================" << endl;
	cout << "Inicia Test para Indice" << endl;
	Indice <int> indice;

	indice.agregar(0, 1);
	indice.agregar(0, 2);
	indice.agregar(0, 5);

	indice.agregar(1, 5);
	indice.agregar(1, 8);
	indice.agregar(1, 7);
	indice.agregar(1, 9);

	indice.agregar(2, 10);
	indice.agregar(2, 9);
	indice.agregar(2, 7);
	indice.agregar(2, 8);
	indice.agregar(2, 8);

	Lista_Id::const_iterator it;


	const Lista_Id &l1= indice.recuperar(0);

	for (it = l1.begin() ; it != l1.end() ; ++it) {
		cout << "List1 dato = 0 : "<< *it << endl;
	}


	indice.recuperar(1);

	for (it = l1.begin() ; it != l1.end() ; ++it) {
		cout << "List1 dato = 1 : "<< *it << endl;
	}

	indice.recuperar(2);
	for (it = l1.begin() ; it != l1.end() ; ++it) {
		cout << "List1 dato = 2 : "<< *it << endl;
	}

	cout << "Fin de Test de Indice" << endl;
}

using namespace std;

void testConsulta() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl << "Inicia Test para Consulta." << endl << endl;

	string datos;

	Consulta consulta;

	consulta.agregarFiltro("Vendedor", "Gonzalo");
	consulta.agregarFiltro("Sucursal", "Avellaneda");

	if (consulta.cantidadFiltros() != 2) {
		cout << "Error en la cantidad de filtros"<< endl;
		errores++;
	}

	if (consulta.filtro(0) != "Sucursal") {
		cout << "Error con filtro \"Sucursal\""<< endl;
		cout << "Rec: "<<consulta.filtro(1) << endl;
		errores++;
	}
	if (consulta.valorFiltro(0) != "Avellaneda") {
		cout << "Error con filtro \"Avellaneda\""<< endl;
		cout << "Rec: "<<consulta.filtro(1) << endl;
		errores++;
	}

	if (consulta.filtro(1) != "Vendedor") {
		cout << "Error con filtro \"Vendedor\""<< endl;
		cout << "Rec: "<<consulta.filtro(1) << endl;
		errores++;
	}
	if (consulta.valorFiltro(1) != "Gonzalo") {
		cout << "Error con valor de filtro \"Gonzalo\""<< endl;
		cout << "Rec: "<<consulta.valorFiltro(1) << endl;
		errores++;
	}


	consulta.agregarEntrada("Marca", "Samsung");
	consulta.agregarEntrada("Camara", "Viva");


	if (consulta.cantidadEntradas() != 2) {
		cout << "Error en la cantidad de Entradas"<< endl;
		errores++;
	}

	if (consulta.entrada(0) != "Camara") {
		cout << "Error con entrada \"Camara\""<< endl;
		cout << "Rec: "<<consulta.filtro(1) << endl;
		errores++;
	}
	if (consulta.valorEntrada(0) != "Viva") {
		cout << "Error con entrada \"Viva\""<< endl;
		cout << "Rec: "<<consulta.entrada(1) << endl;
		errores++;
	}

	if (consulta.entrada(1) != "Marca") {
		cout << "Error con entrada \"Marca\""<< endl;
		cout << "Rec: "<<consulta.entrada(1) << endl;
		errores++;
	}
	if (consulta.valorEntrada(1) != "Samsung") {
		cout << "Error con valor de entrada \"Samsung\""<< endl;
		cout << "Rec: "<<consulta.valorEntrada(1) << endl;
		errores++;
	}

	consulta.defininirAgregacion(PROM, "PrecioLista");
	consulta.agregarResultado("Resultado");
	consulta.agregarResultado("Res2");
	consulta.agregarResultado("Res3");

	if (consulta.cantidadResultados() != 4) {
		cout << "Error en la cantidad de elementos de Resultados en consulta" << endl;
		errores++;
	}

	if (consulta.resultado(0) != "PrecioLista") {
		cout << "Error en resultado de consulta \"PrecioLista\"" << endl;
		cout << "Rec: " << consulta.resultado(0) << endl;
		errores++;
	}
	if (consulta.resultado(1) != "Resultado") {
		cout << "Error en resultado de consulta \"Resultado\"" << endl;
		cout << "Rec: " << consulta.resultado(1) << endl;
		errores++;
	}
	if (consulta.resultado(2) != "Res2") {
		cout << "Error en resultado de consulta \"Res2\"" << endl;
		cout << "Rec: " << consulta.resultado(2) << endl;
		errores++;
	}
	consulta.definirConsultaDeTablaPivote();

	consulta.agregarXTablaP("ABSCISA");
	consulta.agregarXTablaP("ABS-2");
	consulta.agregarYTablaP("ORDENADA");

	consulta.definirComoConsultaCliente();

	datos = consulta.serializar();

	Consulta c2;

	c2.deserializar(datos);

	if (c2.cantidadResultados() != consulta.cantidadResultados()) {
		errores++;
		cout << "Errores en la cantidad de resultados de una consulta a otra deserializada."<< endl;
	}


	if (c2.cantidadFiltros() != consulta.cantidadFiltros()) {
			errores++;
			cout << "Errores en la cantidad de Filtros de una consulta a otra deserializada."<< endl;
	}

	if (c2.cantidadEntradas() != consulta.cantidadEntradas()) {
			errores++;
			cout << "Errores en la cantidad de Entradas de una consulta a otra deserializada."<< endl;
	}

	if (c2.serializar() != datos) {
		cout << "Error en serializar la consulta." << endl;
		cout << "Orig:  " << datos << endl;
		cout << "Copia: " << c2.serializar() << endl;
		errores++;
	}
	else {
		cout << "Serializacion y deserializacion Correcta." << endl;
		cout << "Orig: " << datos << endl;
		cout << "Copia: " << c2.serializar() << endl;
	}


	consulta.limpiar();

	consulta.definirConsultaDeTablaPivote();

	consulta.agregarXTablaP("Vendedor");
	consulta.agregarXTablaP("Sucurasl");
	consulta.agregarXTablaP("CANTIDAD");

	consulta.agregarYTablaP("Producto");
	consulta.agregarYTablaP("PrecioFinal");

	consulta.agregarResultado("PrecioLista");

	c2.limpiar();

	c2.deserializar(consulta.serializar());

	if (c2.serializar() != consulta.serializar()) {
		errores++;
		cout << "Error en la serializacion de consulta de CLiente con Tabla Pivote."<< endl;
		cout <<"Orig: " << consulta.serializar() << endl;
		cout <<"Cop:  " << c2.serializar() << endl;
	}


	if (c2.cantidadResultados() != consulta.cantidadResultados()) {
		errores++;
		cout << "Errores en la cantidad de resultados de una consulta a otra deserializada."<< endl;
	}


	if (c2.cantidadFiltros() != consulta.cantidadFiltros()) {
			errores++;
			cout << "Errores en la cantidad de Filtros de una consulta a otra deserializada."<< endl;
	}

	if (c2.cantidadEntradas() != consulta.cantidadEntradas()) {
			errores++;
			cout << "Errores en la cantidad de Entradas de una consulta a otra deserializada."<< endl;
	}


	if (c2.cantVarXTabla() != consulta.cantVarXTabla()) {
		errores++;
		cout << "Errores en la cant de var de Tabla X en consulta serializada" <<endl;
	}


	if (c2.cantVarYTabla() != consulta.cantVarYTabla()) {
		errores++;
		cout << "Errores en la cant de var de Tabla Y en consulta serializada" <<endl;
	}

	Consulta a1;

	a1.definirComoConsultaAgente();

	a1.agregarCampo("Plata");
	a1.agregarCampo("Direccion");
	a1.agregarCampo("Compra");
	a1.agregarCampo("Rotura");

	if (a1.campo(0) != "Plata") {
		cout << "Error en campo \"Plata\" en consulta de Agente"<< endl;
		cout << "Rec: "<<a1.campo(0) << endl;
		errores++;
	}
	if (a1.campo(1) != "Direccion") {
		cout << "Error en campo \"Direccion\" en consulta de Agente"<< endl;
		cout << "Rec: "<<a1.campo(1) << endl;
		errores++;
	}
	if (a1.campo(2) != "Compra") {
		cout << "Error en campo \"Rotura\" en consulta de Agente"<< endl;
		cout << "Rec: "<<a1.campo(2) << endl;
		errores++;
	}
	if (a1.campo(3) != "Rotura") {
		cout << "Error en campo \"Rotura\" en consulta de Agente"<< endl;
		cout << "Rec: "<<a1.campo(3) << endl;
		errores++;
	}



	string sa1 = a1.serializar();

	Consulta a2;
	a2.deserializar(sa1);


	if (a2.serializar() != sa1) {
		cout << "Error en la serializacion del Agente." << endl;
		cout << "Orig: " << sa1 << endl;
		cout << "Copia: " << a2.serializar() << endl;
		errores++;
	}

	if (errores == 0) {
		cout << "TEST SIN ERRORES+++"<< endl;
	}
	else {
		cout << "CANTIDAD DE ERRORES: "<< errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE CONSULTA " << endl << endl;

}


void testRespuesta() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl << "Inicia Test para Respuesta" << endl << endl;
	Respuesta r1;
	r1.definirColumnas(3);

	r1.agregar("HOLA");	r1.agregar("CHAU");	r1.agregar("SALUDO");	r1.filaCompletada();
	r1.agregar("Anabella");	r1.agregar("Jazmin"); r1.agregar("Johana");	r1.filaCompletada();
	r1.agregar("Julieta");	r1.agregar("Yanina");	r1.agregar("Evelin");	r1.filaCompletada();
	r1.agregar("Julieta");	r1.agregar("Jakelin");	r1.agregar("Barbi"); r1.filaCompletada();

	if (r1.dato(0,0) != "HOLA" || r1.dato(0,1) != "CHAU" || r1.dato(0,2) != "SALUDO") {
		errores++;
		cout << "Errores en la fila 0" << endl;
		cout << "Rec: \"" << r1.dato(0,0) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(0,1) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(0,2) << "\""<< endl;
	}

	if (r1.dato(1,0) != "Anabella" || r1.dato(1,1) != "Jazmin" || r1.dato(1,2) != "Johana") {
		errores++;
		cout << "Errores en la fila 1" << endl;
		cout << "Rec: \"" << r1.dato(1,0) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(1,1) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(1,2) << "\""<< endl;
	}

	if (r1.dato(2,0) != "Julieta" || r1.dato(2,1) != "Yanina" || r1.dato(2,2) != "Evelin") {
		errores++;
		cout << "Errores en la fila 2" << endl;
		cout << "Rec: \"" << r1.dato(2,0) <<"\""<<  endl;
		cout << "Rec: \"" << r1.dato(2,1) <<"\""<<  endl;
		cout << "Rec: \"" << r1.dato(2,2) << "\""<< endl;
	}

	if (r1.dato(3,0) != "Julieta" || r1.dato(3,1) != "Jakelin" || r1.dato(3,2) != "Barbi") {
		errores++;
		cout << "Errores en la fila 3" << "\""<< endl;
		cout << "Rec: \"" << r1.dato(3,0) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(3,1) << "\""<< endl;
		cout << "Rec: \"" << r1.dato(3,2) << "\""<< endl;
	}

	if (r1.cantidadFilas() != 4) {
		cout << "Cantidad de fila incorrectas." << endl;
		cout << "Filas Recibidas:" << r1.cantidadFilas() << endl;
		errores++;
	}

	string datos;
	datos = r1.serializar();

	Respuesta r2;
	r2.deserializar(datos);


	if (r2.serializar() != datos) {
		cout << "Error en la serializacion deserealizacion." << endl;
		cout << "Orig: " << datos << endl;
		cout << "Cop:  " << r2.serializar() << endl;
		cout << "Filas:" << r2.cantidadFilas() << endl;
		r2.deserializar(r2.serializar());
		cout << "Copcp:" << r2.serializar() << endl;
		errores++;
	}

	r2.limpiar();
	Respuesta r3;

	r2.agregar("A"); r2.agregar("B"); r2.agregar("C"); r2.agregar("D"); r2.filaCompletada();
	r2.agregar("EE"); r2.agregar("FF"); r2.agregar("GG"); r2.agregar("HH"); r2.filaCompletada();
	r2.agregar("III"); r2.agregar("JJJ"); r2.agregar("KKK"); r2.agregar("LLL"); r2.filaCompletada();


	r3.deserializar(r2.serializar());
	r3.deserializar(r3.serializar());
	r3.deserializar(r3.serializar());
	r3.deserializar(r3.serializar());

	if (r2.serializar() != r3.serializar()) {
		cout << "Error en la serializacion deserealizacion." << endl;
		cout << "Orig: " << r2.serializar() << endl;
		cout << "Cop:  " << r3.serializar() << endl;
		cout << "Filas:" << r3.cantidadFilas() << endl;
		r3.deserializar(r3.serializar());
		cout << "Copcp:" << r3.serializar() << endl;
		errores++;
	}

	Respuesta r4, r5;

	r4.definirColumnas(6);
	r4.definirID(234);


	r5.deserializar(r4.serializar());
	r5.deserializar(r5.serializar());
	r5.deserializar(r5.serializar());
	r5.deserializar(r5.serializar());

	if (r4.serializar() != r5.serializar()) {
		cout << "Error en serializacion de columnas nada mas."<< endl;
		cout << "Orig: "<< r4.serializar() << endl;
		cout << "Cop:  "<< r5.serializar() << endl;
				errores++;
	}



	Respuesta r1Fila;

	r1Fila.definirColumnas(3);
	r1Fila.agregar("asd");
	r1Fila.agregar("asd");
	r1Fila.agregar("asd");
	r1Fila.filaCompletada();

	string sr1Fila = r1Fila.serializar();

	r4.deserializar(sr1Fila);

	if (r4.serializar() != r1Fila.serializar()) {
		cout << "Error en serializacion para Respuesta de Una Fila"<< endl;
		cout << "Orig: "<< r1Fila.serializar() << endl;
		cout << "Cop:  "<< r4.serializar() << endl;
		errores++;
	}


	if (errores == 0) {
		cout << "Test sin Errores++" << endl;
	}
	else {
		cout << "Errores en Test: "<<errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE RESPUESTA" << endl;
}


void testMFechas() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl << "Inicia el Test para M_Fechas" << endl << endl;

	M_Fechas mf;

	Fecha fecha = mf.fecha(17,5,1990);
	if (fecha != "19900517") {
		cout <<" Error en metodo \"fecha\"" << endl;
		errores++;
	}

	cout << "1 mes 2009: " << mf.mes(1,"2009") << endl;
	cout << "2 mes 2009: " << mf.mes(2,"2009") << endl;
	cout << "5 mes 2009: " << mf.mes(5,"2009") << endl;
	cout << "6 mes 2009: " << mf.mes(6,"2009") << endl;
	cout << "12 mes 2009: " << mf.mes(12,"2009") << endl;

	cout << endl;

	cout << "1 bimestre 2010: " <<mf.bimestre(1, "2010") << endl;
	cout << "2 bimestre 2010: " <<mf.bimestre(2, "2010") << endl;

	cout << "5 bimestre 2010: " <<mf.bimestre(5, "2010") << endl;
	cout << "6 bimestre 2010: " <<mf.bimestre(6, "2010") << endl;

	cout << endl;


	cout << "1 trimestre 2000: " << mf.trimestre(1, "2000") << endl;
	cout << "2 trimestre 2000: " << mf.trimestre(2, "2000") << endl;
	cout << "4 trimestre 2000: " << mf.trimestre(4, "2000") << endl;

	cout << endl;

	cout << "1 cuatrimestre 2000: " << mf.cuatrimestre(1, "2000") << endl;
	cout << "2 cuatrimestre 2000: " << mf.cuatrimestre(2, "2000") << endl;
	cout << "3 cuatrimestre 2000: " << mf.cuatrimestre(3, "2000") << endl;

	cout << endl;

	cout << "1 semestre 1990: " << mf.semestre(1,"1990") << endl;
	cout << "2 semestre 1990: " << mf.semestre(2,"1990") << endl;


	Fecha f1, f2;
	fecha = mf.trimestre(2, "1990");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 != "19900401" || f2 != "19900701") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "2 Trimestre de 1990: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	fecha = mf.bimestre(1, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1!="19990101" || f2!="19990301") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "1 Bimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}



	fecha = mf.bimestre(4, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 != "19990701" || f2 != "19990901") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "4 Bimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}




	fecha = mf.bimestre(5, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 != "19990901" || f2 != "19991101") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "5 Bimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}



	fecha = mf.bimestre(6, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 != "19991101" || f2 != "20000101") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "6 Bimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;

	}


	fecha = mf.cuatrimestre(1, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 != "19990101" || f2 != "19990501") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "1 cuatrimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}



	fecha = mf.trimestre(4, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1!="19991001" || f2!="20000101") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "4 trimestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	fecha = mf.semestre(1, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1!="19990101" || f2!="19990701") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "1 Semestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}

	fecha = mf.semestre(2, "1999");
	mf.desarmar(fecha, f1, f2);
	if (mf.esRango(fecha) == false || f1 !="19990701" || f2!="20000101") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << endl;
		cout << "2 Semestre de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	fecha = mf.mes(1, "1999");
	mf.desarmar(fecha, f1, f2);
	cout << endl;
	if (mf.esRango(fecha) == false || f1!="19990101" || f2!="19990201") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "1 mes de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}

	fecha = mf.mes(3, "1999");
	mf.desarmar(fecha, f1, f2);
	cout << endl;
	if (mf.esRango(fecha) == false || f1 !="19990301" || f2!="19990401") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "3 mes de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}

	fecha = mf.mes(4, "1999");
	mf.desarmar(fecha, f1, f2);
	cout << endl;
	if (mf.esRango(fecha) == false || f1!="19990401" || f2!="19990501") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "4 mes de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	fecha = mf.mes(6, "1999");
	mf.desarmar(fecha, f1, f2);
	cout << endl;
	if (mf.esRango(fecha) == false || f1 != "19990601" || f2!="19990701") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "6 mes de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	fecha = mf.mes(12, "1999");
	mf.desarmar(fecha, f1, f2);
	cout << endl;
	if (mf.esRango(fecha) == false || f1!="19991201" || f2!="20000101") {
		errores++;
		cout << "Error la fecha con rango" << endl;
		cout << "12 mes de 1999: "<< endl;
		cout << "Inferior: " << f1 << endl;
		cout << "Superior: " << f2 << endl;
	}


	if (mf.esFechaConvecional("12-12-2012") == false) {
		errores++;
		cout << "Error en metodo esFechaConvecional." << endl;
		cout << "Mal calculo de fecha convencional."<< endl;
	}

	if (mf.esFechaConvecional("12122012")) {
		errores++;
		cout << "Error en metodo esFechaConvecional." << endl;
		cout << "Por ser fecha no convecional"<< endl;
	}

	if (mf.esFechaConvecional("12-122012")) {
		errores++;
		cout << "Error en metodo esFechaConvecional." << endl;
	}


	if (mf.esFechaConvecional("12-14-2002")) {
		errores++;
		cout << "Error: no es fecha convencional 12-14-2002" << endl;
	}

	if (mf.esFechaConvecional("33-11-2000")) {
		errores++;
		cout << "Error: no es fecha convencional 12-14-2000" << endl;
	}

	if (mf.esFechaConvecional("0-11-2000")) {
		errores++;
		cout << "Error: no es fecha convencional 12-14-2000" << endl;
	}


	if (!mf.esFechaConvecional("12-11-2000")) {
		errores++;
		cout << "Error: en no validar fecha correcta, 12-11-2000" << endl;
	}

	if (mf.esFechaConvecional("--")) {
		errores++;
		cout << "Error: validar fecha vacia" << endl;
	}


	if (mf.esFechaConvecional("-asd-asd")) {
		errores++;
		cout << "Error: en validad cualquier cosa" << endl;
	}



	Fecha fanio = mf.anio("2012");
	mf.desarmar(fanio, f1, f2);

	if (!mf.esRango(fanio) || f1 !="20120101" || f2 != "20130101") {
		errores++;
		cout << "Error en fecha anio" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fanio = mf.anio("2000");
	mf.desarmar(fanio, f1, f2);
	if (!mf.esRango(fanio) || f1 !="20000101" || f2 != "20010101") {
		errores++;
		cout << "Error en fecha anio" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	/*
	 * Pruebas para semanas
	 */

	Fecha fsemana = mf.semana(1,"2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120101" || f2 != "20120108") {
		errores++;
		cout << "Error en fecha de semana 1" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(2, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120108" || f2 != "20120115") {
		errores++;
		cout << "Error en fecha de semana 2" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(3, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120115" || f2 != "20120122") {
		errores++;
		cout << "Error en fecha de semana 3" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(4, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120122" || f2 != "20120129") {
		errores++;
		cout << "Error en fecha de semana 4" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(5, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120129" || f2 != "20120205") {
		errores++;
		cout << "Error en fecha de semana 5" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(5, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120129" || f2 != "20120205") {
		errores++;
		cout << "Error en fecha de semana 5" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(5, "2013");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20130129" || f2 != "20130205") {
		errores++;
		cout << "Error en fecha de semana 5 no bisiesto" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(6, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120205" || f2 != "20120212") {
		errores++;
		cout << "Error en fecha de semana 6" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(7, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120212" || f2 != "20120219") {
		errores++;
		cout << "Error en fecha de semana 7" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(8, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120219" || f2 != "20120226") {
		errores++;
		cout << "Error en fecha de semana 8" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(9, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120226" || f2 != "20120304") {
		errores++;
		cout << "Error en fecha de semana 9" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(9, "2013");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20130226" || f2 != "20130305") {
		errores++;
		cout << "Error en fecha de semana 9 no bisiesto" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(10, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120304" || f2 != "20120311") {
		errores++;
		cout << "Error en fecha de semana 10" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(11, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120311" || f2 != "20120318") {
		errores++;
		cout << "Error en fecha de semana 11" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(12, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120318" || f2 != "20120325") {
		errores++;
		cout << "Error en fecha de semana 12" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(13, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120325" || f2 != "20120401") {
		errores++;
		cout << "Error en fecha de semana 13" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(13, "2013");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20130326" || f2 != "20130402") {
		errores++;
		cout << "Error en fecha de semana 13 no bisiesto" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(14, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120401" || f2 != "20120408") {
		errores++;
		cout << "Error en fecha de semana 14" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(15, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120408" || f2 != "20120415") {
		errores++;
		cout << "Error en fecha de semana 15" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(18, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120429" || f2 != "20120506") {
		errores++;
		cout << "Error en fecha de semana 18" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(21, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120520" || f2 != "20120527") {
		errores++;
		cout << "Error en fecha de semana 21" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(22, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120527" || f2 != "20120603") {
		errores++;
		cout << "Error en fecha de semana 22" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(26, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120624" || f2 != "20120701") {
		errores++;
		cout << "Error en fecha de semana 25" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(31, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120729" || f2 != "20120805") {
		errores++;
		cout << "Error en fecha de semana 31" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(32, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120805" || f2 != "20120812") {
		errores++;
		cout << "Error en fecha de semana 32" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(35, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120826" || f2 != "20120902") {
		errores++;
		cout << "Error en fecha de semana 35" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(37, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120909" || f2 != "20120916") {
		errores++;
		cout << "Error en fecha de semana 37" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(40, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20120930" || f2 != "20121007") {
		errores++;
		cout << "Error en fecha de semana 40" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(41, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121007" || f2 != "20121014") {
		errores++;
		cout << "Error en fecha de semana 41" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(43, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121021" || f2 != "20121028") {
		errores++;
		cout << "Error en fecha de semana 43" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(44, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121028" || f2 != "20121104") {
		errores++;
		cout << "Error en fecha de semana 44" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(48, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121125" || f2 != "20121202") {
		errores++;
		cout << "Error en fecha de semana 48" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(49, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121202" || f2 != "20121209") {
		errores++;
		cout << "Error en fecha de semana 49" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(51, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121216" || f2 != "20121223") {
		errores++;
		cout << "Error en fecha de semana 51" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(52, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121223" || f2 != "20121230") {
		errores++;
		cout << "Error en fecha de semana 52" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(53, "2012");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20121230" || f2 != "20130101") {
		errores++;
		cout << "Error en fecha de semana 53" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}

	fsemana = mf.semana(53, "2013");
	mf.desarmar(fsemana, f1, f2);
	if (!mf.esRango(fsemana) || f1 != "20131231" || f2 != "20140101") {
		errores++;
		cout << "Error en fecha de semana 53 no bisiesto" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	fsemana = mf.semana(78, "2000");
	mf.desarmar(fsemana, f1, f2);
	if (mf.esRango(fsemana) || f1 != "" || f2 != "") {
		errores++;
		cout << "Error en fecha de semana 78 no bisiesto" << endl;
		cout << "Inf: " << f1 << endl;
		cout << "Sup: " << f2 << endl;
	}


	if (errores == 0) {
		cout << "TEST SIN ERRORES++"<< endl;
	}
	else {
		cout << "TEST CON ERRORES: "<< errores << endl;
		exit(0);
	}

	cout << endl << "FIN DE TEST DE M_Fechas" << endl;

}

void testIndFechas() {
	cout << "=================================================" << endl;
	cout << "Inicia el test para IndiceDeFechas" << endl;
	int errores = 0;


	IndiceDeFechas indice;

#define F1 19900110
#define F2 19900210
#define F3 19900212
#define F4 19900220
#define F5 19900301
#define F6 19900620
#define F7 19900601
#define F8 19901001
#define F9 19901223

	cout << "Fecha F1 " << endl;

	M_Fechas mf;

	indice.guardarFecha(mf.convertir(F1),F1);
	indice.guardarFecha(mf.convertir(F2),F2);
	indice.guardarFecha(mf.convertir(F3),F3);
	indice.guardarFecha(mf.convertir(F4),F4);
	indice.guardarFecha(mf.convertir(F5),F5);
	indice.guardarFecha(mf.convertir(F6),F6);
	indice.guardarFecha(mf.convertir(F7),F7);
	indice.guardarFecha(mf.convertir(F8),F8);
	indice.guardarFecha(mf.convertir(F9),F9);

	Fecha consulta = mf.cuatrimestre(1, "1990");
	Lista_Id::const_iterator it;
	Lista_Id lista;
	indice.recuperar(consulta, lista);

	cout << "Fechas del 1 cuatrimestre de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}

	consulta = mf.semestre(2, "1990");
	indice.recuperar(consulta, lista);
	cout << endl <<"Fechas del 2 semestre de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}

	consulta = mf.mes(3, "1990");
	indice.recuperar(consulta, lista);
	cout << endl <<"Fechas del 3 mes de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}

	consulta = mf.mes(10, "1990");
	indice.recuperar(consulta, lista);
	cout << endl <<"Fechas del 10 mes de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}

	consulta = mf.mes(7, "1990");
	indice.recuperar(consulta, lista);
	cout << endl <<"Fechas del 7 mes de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}

	consulta = mf.mes(2, "1990");
	indice.recuperar(consulta, lista);
	cout << endl <<"Fechas del 2 mes de 1990" << endl;
	for ( it = lista.begin() ; it != lista.end() ; ++it) {
		cout << "Fecha: " << *it << endl;
	}


	if (errores == 0) {
		cout << "TEST SIN ERRORES++" << endl;
	}
	else {
		cout << "TEST CON ERRORES: " << errores << endl;
		exit(0);
	}

	cout << "FIN DE TEST DE IndiceDeFechas." << endl;
}

#include "../servidor/servidor/VerificadorEntradasH.h"

void testValidadorEntrada() {

	string ruta = "./org.txt";
	string c1 = "Dimensiones = { Sucursal, Vendedor, Fecha, Marca, Producto}";
	string c2 = "Hechos = { PrecioLista, PrecioVenta }";

	std::fstream arch(ruta.c_str(), fstream::out);
	arch << c1;
	arch << std::endl;
	arch << c2;

	arch.close();


	cout << "====================================" << endl;
	cout << "Inicia test para validador Entrada" << endl;

int errores = 0;
	VerificadorEntradasH verif;

	Consulta c;
	Organizacion::cargarDefiniciones(ruta);

	c.definirComoConsultaAgente();

	c.agregarCampo("SucursalX");
	c.agregarCampo("VendedorX");
	c.agregarCampo("FechaX");
	c.agregarCampo("MarcaX");
	c.agregarCampo("ProductoX");

	c.agregarCampo("PrecioListaX");
	c.agregarCampo("PrecioVentaX");


	if (verif.verificarEntrada(c) == false) {
		cout << "Error en entrada correcta" << endl;
		errores++;
	}


	if (errores == 0) {
		cout << "Test sin Errores++"<< endl;
	}
	else {
		cout << "Test con Errores: "<< errores << endl;
		cout << "Fin De Test para Verificador Entrada" << endl;
		exit(0);
	}

	cout << "Fin De Test para Verificador Entrada" << endl;

	// borro el archivo usado para la prueba
	std::string comandoBorrar = "rm ";
	comandoBorrar += ruta;
	system(comandoBorrar.c_str());

}
