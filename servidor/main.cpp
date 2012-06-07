#include <iostream>
#include <string>
#include "Servidor.h"
#include "Definiciones.h"

void assert_prueba(bool resultado) {
	std::cout << ((resultado)? "OK" : "ERROR") << std::endl;
}

int main(int argc, char **argv) {
	Servidor serv;
	std::string a("");
	std::string q("q");
	while (a != q) {
		std::cout << "ingrese 'q' para salir: ";
		std::cin >> a;
		std::cout << std::endl;
	}
	return 0;
}

