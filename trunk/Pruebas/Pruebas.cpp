/*
 * Pruebas.cpp
 *
 *  Created on: 03/06/2012
 *      Author: migue
 */
#include "Pruebas.h"
#include "../comun/Organizacion.h"
#include "../servidor/MotorDeConsultas/ArchivoDeDatos.h"
#include <iostream>
#include <fstream>
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"
#include "../comun/M_Fechas.h"
#include "../servidor/MotorDeConsultas/BaseDeDatos.h"
#include "../servidor/servidor/VerificadorConsultasH.h"
#include "../servidor/servidor/VerificadorEntradasH.h"
#include <stdlib.h>
#include "../comun/GenRegistros.h"
using namespace std;


void testSerializaciones() {

}

void testOrganizacion() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl <<"Inicia Test Para Organizacion" << endl;

	char *ruta = "./Fuente/org.txt";
	char *c1 = "Dimensiones = { Marca,  Fecha, Bonificacion, Producto, Vendedor,HOGAR, Organizacion}";
	char *c2 = "Hechos = { Precio, PrecioVenta ,PrecioLista }";

	std::fstream arch(ruta, fstream::out);
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
	}

	cout << "FIN DE TEST DE Organizacion." << endl;
}


void testValidadorConsulta() {
	cout << "=================================================" << endl;
	cout << "Inicia el Test para el Verificador de Consulta."<< endl;

	// Creo y configuro la organizacion.
	char* rutaOrganizacion = "./organizacion.txt";
	{
		char* dimensiones = "Dimensiones = { Sucursal, Vendedor, Producto}";
		char* hechos = "Hechos = {PrecioLista, PrecioFinal}";
		fstream archOrg(rutaOrganizacion, fstream::out);

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
}


void testArchivoDeDatos() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << endl << "Inicia Test para ArchivoDeDatos" << endl;

	ArchivoDeDatos arch("archDatos.txt");
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
}


void testInterseccion() {
	cout << "=================================================" << endl;
	cout << "Inicia test para Interseccion" << endl;
	int errores = 0;


	BaseDeDatos bdd("ruta.txt");

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
}

void testFiltrar() {
	cout << "=================================================" << endl;
	int errores = 0;
	cout << "Inicio de Test para BaseDeDatos::Filtrar" << endl;

	// Creo y configuro la organizacion.
	char* rutaOrganizacion = "./organizacion.txt";
	{
		char* dimensiones = "Dimensiones = { Sucursal, Vendedor, Producto}";
		char* hechos = "Hechos = {PrecioLista}";
		fstream archOrg(rutaOrganizacion, fstream::out);

		archOrg << dimensiones;
		archOrg << endl;
		archOrg << hechos;

		archOrg.close();
	}
	Organizacion::cargarDefiniciones(rutaOrganizacion);

	BaseDeDatos bdd("ruta.txt");
	Consulta cAgente;
	cAgente.definirComoConsultaAgente();

	cAgente.agregarCampo("Avellaneda");
	cAgente.agregarCampo("Santiago");
	cAgente.agregarCampo("Samsung Galaxy");
	cAgente.agregarCampo("1500");

	bdd.agregarEntrada(cAgente);

	// Nuevo registro en la base;

	cAgente.limpiar();
	cAgente.definirComoConsultaAgente();

	cAgente.agregarCampo("Avellaneda");
	cAgente.agregarCampo("Gonzalo");
	cAgente.agregarCampo("Samsung Galaxy Pro");
	cAgente.agregarCampo("1500");

	bdd.agregarEntrada(cAgente);

	// Nuevo registro en la base;

	cAgente.limpiar();
	cAgente.definirComoConsultaAgente();

	cAgente.agregarCampo("Lomas");
	cAgente.agregarCampo("Gonzalo");
	cAgente.agregarCampo("Samsung Galaxy Pro Young");
	cAgente.agregarCampo("1400");

	bdd.agregarEntrada(cAgente);

	// Nuevo registro en la base;

	cAgente.limpiar();
	cAgente.definirComoConsultaAgente();

	cAgente.agregarCampo("Avellaneda");
	cAgente.agregarCampo("Pablo");
	cAgente.agregarCampo("Samsung E-215L");
	cAgente.agregarCampo("1999");

	bdd.agregarEntrada(cAgente);

	// Nuevo registro en la base;

	cAgente.limpiar();
	cAgente.definirComoConsultaAgente();

	cAgente.agregarCampo("Lomas");
	cAgente.agregarCampo("Gonzalo");
	cAgente.agregarCampo("Samsung Tablet");
	cAgente.agregarCampo("1700");

	bdd.agregarEntrada(cAgente);


	Consulta consulta;
	consulta.agregarFiltro("Vendedor","Gonazalo");



	if (errores == 0) {
		cout << "Test sin Errores++" << endl;
	}
	else {
		cout << "Test con errores: " << errores << endl;
	}

	cout << "Fin de Test de BaseDeDatos::Filtrar" << endl;
}

void testAgregacion() {
	cout << "La agregacion Funciona!!!" << endl;
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
			cout.left;
			cout.fill('.');
			cout<< resp.dato(i,j) << "|";
		}
		cout << endl;
	}
}

void testBaseDeDatos() {
	cout << "=================================================" << endl;
	cout << endl << "Inicia el Test para BaseDeDatos." << endl;
	int errores = 0;

	M_Fechas mf;


	// Creo y configuro la organizacion.
	char* rutaOrganizacion = "./organizacion.txt";
	{

	std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
	std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
	fstream archOrg(rutaOrganizacion, fstream::out);


	archOrg << dimensiones;
	archOrg << endl;
	archOrg << hechos;

	archOrg.close();

	}

	Organizacion::cargarDefiniciones(rutaOrganizacion);

	string rutaDatos = "./datos-bdd.txt";

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
			cout.left;
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
	}

	cout << "Fin de Test de BaseDeDatos" << endl;
}

void testGeneradorRegistros() {
	// Creo y configuro la organizacion.
	char* rutaOrganizacion = "./organizacion.txt";
	{

	std::string dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
	std::string hechos = "Hechos = {PrecioLista, PrecioFinal }";
	fstream archOrg(rutaOrganizacion, fstream::out);


	archOrg << dimensiones;
	archOrg << endl;
	archOrg << hechos;

	archOrg.close();

	}

	Organizacion::cargarDefiniciones(rutaOrganizacion);

	cout << "====================================================" << endl;
	cout << "Inicia el Test de Generador De Registros." << endl;

	int errores = 0;

	string rutaDatos = "./datosRegGen.dat";
	BaseDeDatos bdd(rutaDatos);

	long cantReg = 200;

	generarRegistros(bdd, cantReg);

	//for (Id_Registro id = 0 ; i <)


	cout << "FIN DE TEST DE Generador de Registros." << endl;

}

void testPesadoSeparador() {
	cout << "=====================================" << endl;
	int errores = 0;
	cout << "Inicia Test para separador" << endl;

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
	}


	cout << "Fin de Test Pesado para Separador" << endl;
}
