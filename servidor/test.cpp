#include <iostream>
#include <string>
#include "Socket.h"
#include "Definiciones.h"

void assert_prueba(bool resultado) {
	std::cout << ((resultado)? "OK" : "ERROR") << std::endl;
}

int main(int argc, char **argv) {
	std::string cons1("C1");
	Consulta c1(cons1);	/*
	Consulta c2("C2");
	Consulta c3("C3");
	Consulta c4("C4");
	Consulta c5("C5");*/
	std::string vacio("");
	Respuesta r(vacio);
	Socket* sock = new Socket((Puerto)4321);
	std::string host("localhost");
	sock->conectar(host);
	std::cout << "conectando con el servidor:" << std::endl;
	assert_prueba(sock->conectado());
	std::cout << "mandando dato 1:" << std::endl;
	assert_prueba(sock->enviar(c1));
	std::cout << "esperando respuesta 1:" << std::endl;
	assert_prueba(sock->recibir(r));
	std::cout << "recibio";
	assert_prueba(r.serializar() == c1.serializar());
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
