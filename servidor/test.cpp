#include <iostream>
#include <string>
#include "../comun/Socket.h"
#include "../comun/Definiciones.h"
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"
#include "../comun/Organizacion.h"
#include "../comun/Hilo.h"
#include "servidor/Servidor.h"

#define MAX_CLIENTES_SIMULTANEOS 2
#define MAX_AGENTES_SIMULTANEOS 2

#define PUERTO_CLIENTE 4321
#define PUERTO_AGENTE 12345

std::string vendedores[] = {"Seba", "Migue", "Piba", "Chabon", "Nacho"};
std::string sucursales[] = {"Mordor", "Varela", "Moron", "Venus", "Lomas"};
std::string fechas[] = {"20111212", "20080909", "20081230", "20120101", "19900502" };
std::string productos[] = {"chupetin", "notebook", "ferrari", "felicidad", "titulos de ingeniero"};

void assert_prueba(bool resultado) {
	std::cout << ((resultado)? "OK PRUEBA" : "ERROR PRUEBA") << std::endl;
}

void imprimirRespuesta(Respuesta& r) {

	std::cout << ">>>Datos de Respuesta: " << r.serializar() << endl;

	for (unsigned i = 0; i < r.cantidadFilas(); i++) {
		std::cout << "::";
		for (unsigned j = 0; j < r.cantidadColumnas(); j++) {
			std::cout.width(11);
			std::cout.fill('.');
			std::cout << r.dato(i,j) << "|";
		}
		std::cout << std::endl;
	}
}

class clienteDummy: public Hilo {
private:
	static unsigned instancias;
	unsigned id;
public:
	clienteDummy() {
		id = ++instancias;
	}
	~clienteDummy() {}
	void correr() {
		std::cout << "=========PRUEBA CLIENTE EN THREAD " << id << " ==========" << endl;
		Consulta c[5];
		for (unsigned i = 0; i < 5; ++i) {
			c[i].definirComoConsultaCliente();
			c[i].agregarFiltro("Vendedor", vendedores[i].c_str());
			c[i].agregarFiltro("Sucursal", sucursales[i].c_str());
			c[i].agregarResultado("Vendedor");
		}
		Socket* sock = new Socket((Puerto)4321);
		std::string host("localhost");
		sock->conectar(host);
		Respuesta r;
		for (unsigned i = 0; i < 5; ++i) {
			std::cout << "conectando con el servidor:" << std::endl;
			assert_prueba(sock->conectado());
			std::cout << "mandando dato " << i << std::endl;
			assert_prueba(sock->enviar(c[i]));
			std::cout << "esperando respuesta " << i << std::endl;
			assert_prueba(sock->recibir(r));
			imprimirRespuesta(r);
		}
		sock->desconectar();
		delete sock;
	}
};

unsigned clienteDummy::instancias = 0;

class agenteDummy: public Hilo {
private:
	static unsigned instancias;
	unsigned id;
public:
	agenteDummy() {
		id = ++instancias;
	}
	~agenteDummy() {}
	void correr() {
		std::cout << "=========PRUEBA AGENTE EN THREAD " << id << " ==========" << endl;
		Consulta c[5];		
		for (unsigned i = 0; i < 5; ++i) {
			c[i].definirComoConsultaAgente();
			c[i].agregarCampo(vendedores[i].c_str());
			c[i].agregarCampo(sucursales[i].c_str());
			c[i].agregarCampo(fechas[i].c_str());
			c[i].agregarCampo(productos[i].c_str());
		}
		Socket* sock = new Socket((Puerto)PUERTO_AGENTE);
		std::string host("localhost");
		sock->conectar(host);
		Respuesta r;
		for (unsigned i = 0; i < 5; ++i) {
			std::cout << "conectando con el servidor:" << std::endl;
			assert_prueba(sock->conectado());
			std::cout << "mandando dato " << i << std::endl;
			assert_prueba(sock->enviar(c[i]));
			std::cout << "esperando respuesta "<< i << std::endl;
			assert_prueba(sock->recibir(r));
			// imprimirRespuesta(r);
			std::cout << "Mensaje interno " << r.mensajeInterno() << std::endl;
		}
		sock->desconectar();
		delete sock;
	}
};

unsigned agenteDummy::instancias = 0;

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


void pruebaAgentes() {
	Consulta c[5];
	std::string vendedores[] = {"Seba", "Migue", "Piba", "Chabon", "Nacho"};
	std::string sucursales[] = {"Mordor", "Varela", "Moron", "Venus", "Lomas"};
	std::string fechas[] = {"20111212", "20080909", "20081230", "20120101", "19900502" };
	std::string productos[] = {"chupetin", "notebook", "ferrari", "felicidad", "titulos de ingeniero"};
	for (unsigned i = 0; i < 5; ++i) {
		c[i].limpiar();
		c[i].definirComoConsultaAgente();

		c[i].agregarCampo(sucursales[i].c_str());
		c[i].agregarCampo(vendedores[i].c_str());

		c[i].agregarCampo(fechas[i].c_str());
		c[i].agregarCampo(productos[i].c_str());

		c[i].agregarCampo("220");
		c[i].agregarCampo("230");
	}
	Socket* sock = new Socket((Puerto)PUERTO_AGENTE);
	std::string host("localhost");
	sock->conectar(host);
	Respuesta r;
	for (unsigned i = 0; i < 5; ++i) {
		std::cout << "conectando con el servidor:" << std::endl;
		assert_prueba(sock->conectado());
		std::cout << "mandando dato " << i << std::endl;
		assert_prueba(sock->enviar(c[i]));
		std::cout << "esperando respuesta "<< i << std::endl;
		assert_prueba(sock->recibir(r));
		std::cout << "Mensaje interno " << r.mensajeInterno() << std::endl;
	}
	sock->desconectar();
	delete sock;
}

void pruebaClientes() {
	std::cout << "===========PRUEBA CLIENTE SIMPLE===========" << std::endl;
	Consulta c[5];
	for (unsigned i = 0; i < 5; ++i) {
		c[i].definirComoConsultaCliente();
		//c[i].agregarFiltro("Vendedor", vendedores[i].c_str());
		//c[i].agregarFiltro("Sucursal", sucursales[i].c_str());
		c[i].agregarResultado(Organizacion::nombreCampo(i)); // "Vendedor"
	}
	Socket* sock = new Socket((Puerto)PUERTO_CLIENTE);
	std::string host("localhost");
	sock->conectar(host);
	Respuesta r;
	for (unsigned i = 0; i < 5; ++i) {
		std::cout << "conectando con el servidor:" << std::endl;
		assert_prueba(sock->conectado());
		std::cout << "mandando dato " << i << std::endl;
		assert_prueba(sock->enviar(c[i]));
		std::cout << "esperando respuesta " << i << std::endl;
		assert_prueba(sock->recibir(r));
		imprimirRespuesta(r);
	}
	sock->desconectar();
	delete sock;
}

void pruebaAgentesMultiples() {
	agenteDummy agentes[MAX_AGENTES_SIMULTANEOS];
	for (unsigned i = 0; i < MAX_AGENTES_SIMULTANEOS; ++i) {
		agentes[i].iniciar();
	}
	for (unsigned i = 0; i < MAX_AGENTES_SIMULTANEOS; ++i) {
		agentes[i].sincronizar();
	}
}

void pruebaClientesMultiples() {
	clienteDummy clientes[MAX_CLIENTES_SIMULTANEOS];
	agenteDummy agentes[MAX_AGENTES_SIMULTANEOS];
	for (unsigned i = 0; i < MAX_CLIENTES_SIMULTANEOS; ++i)
		clientes[i].iniciar();
	for (unsigned i = 0; i < MAX_AGENTES_SIMULTANEOS; ++i)
		agentes[i].iniciar();
	for (unsigned i = 0; i < MAX_CLIENTES_SIMULTANEOS; ++i)
		clientes[i].sincronizar();
	for (unsigned i = 0; i < MAX_AGENTES_SIMULTANEOS; ++i)
		agentes[i].sincronizar();	
}

void pruebaAmbosMultiples() {
	clienteDummy clientes[MAX_CLIENTES_SIMULTANEOS];
	for (unsigned i = 0; i < MAX_CLIENTES_SIMULTANEOS; ++i) {
		clientes[i].iniciar();
	}
	for (unsigned i = 0; i < MAX_CLIENTES_SIMULTANEOS; ++i) {
		clientes[i].sincronizar();
	}
}

int main(int argc, char **argv) {
	inicializar();
	Servidor server;
	cout << "===================================================" << endl;
	pruebaAgentes();
	cout << "===================================================" << endl;
	pruebaClientes();
	cout << "===================================================" << endl;
	//pruebaAgentesMultiples();
	cout << "===================================================" << endl;
	//pruebaClientesMultiples();
	cout << "===================================================" << endl;
	//pruebaAmbosMultiples();
	return 0;
}
