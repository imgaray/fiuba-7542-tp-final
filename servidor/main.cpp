#include <iostream>
#include <string>
#include "servidor/Servidor.h"
#include "../comun/Definiciones.h"

//void assert_prueba(bool resultado) {
//	std::cout << ((resultado)? "OK" : "ERROR") << std::endl;
//}

int main__(int argc, char **argv) {
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

