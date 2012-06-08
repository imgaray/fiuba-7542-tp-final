#include <iostream>
#include <string>
#include "Socket.h"
#include "Definiciones.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "Organizacion.h"

void assert_prueba(bool resultado) {
	std::cout << ((resultado)? "OK" : "ERROR") << std::endl;
}

void inicializar() {
	const char* rutaOrganizacion = "./organizacion.txt";
	const char* dimensiones = "Dimensiones = { Sucursal, Vendedor, Fecha, Producto}";
	const char* hechos = "Hechos = {PrecioLista, PrecionFinal }";
	std::fstream archOrg(rutaOrganizacion, std::fstream::out);
	archOrg << dimensiones;
	archOrg << std::endl;
	archOrg << hechos;
	archOrg.close();
	Organizacion::cargarDefiniciones(rutaOrganizacion);
}

int main(int argc, char **argv) {
	inicializar();
	Consulta c[5];
	std::string vendedores[] = {"Seba", "Migue", "Piba", "Chabon", "Nacho"};
	std::string sucursales[] = {"Mordor", "Varela", "Moron", "Venus", "Lomas"};
	std::string fechas[] = {"20111212", "20080909", "20081230", "20120101", "19900502" };
	std::string productos[] = {"chupetin", "notebook", "ferrari", "felicidad", "titulos de ingeniero"};
	for (unsigned i = 0; i < 5; ++i) {
		c[i].definirComoConsultaAgente();
		c[i].agregarCampo(vendedores[i].c_str());
		c[i].agregarCampo(sucursales[i].c_str());
		c[i].agregarCampo(fechas[i].c_str());
		c[i].agregarCampo(productos[i].c_str());
	}
	Socket* sock = new Socket((Puerto)12345);
	std::string host("localhost");
	sock->conectar(host);
	Respuesta r;
	for (unsigned i = 0; i < 5; ++i) {
		std::cout << "conectando con el servidor:" << std::endl;
		assert_prueba(sock->conectado());
		std::cout << "mandando dato 1:" << std::endl;
		assert_prueba(sock->enviar(c[i]));
		std::cout << "esperando respuesta 1:" << std::endl;
		assert_prueba(sock->recibir(r));
		for (unsigned i = 0; i < r.cantidadFilas(); ++i) {
			std::cout << "::";
			for (unsigned j = 0; j < r.cantidadColumnas(); ++j) {
				std::cout.width(11);
				std::cout.fill('.');
				std::cout << r.dato(i,j) << "|";
			}
			std::cout << std::endl;
		}
	}
	std::string a("");
	std::string q("q");
	while (a != q) {
		std::cout << "ingrese 'q' para salir: ";
		std::cin >> a;
		std::cout << std::endl;
	}
	sock->desconectar();
	delete sock;
	return 0;
}
