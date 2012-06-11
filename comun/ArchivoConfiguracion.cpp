#include "ArchivoConfiguracion.h"

#define SEPARADOR '='

// por lo pronto, el formato correcto sera que haya un solo separador

bool ArchivoConfiguracion::formatoCorrecto(std::string& linea) {
	return (linea.find_first_of(SEPARADOR) == linea.find_last_of(SEPARADOR));
}

ArchivoConfiguracion::ArchivoConfiguracion(char* ruta) {
	std::fstream archivo(ruta);
	if (!archivo) {
		// manejar el caso de primer uso
	} else {
		std::string aux;
		while(!archivo.eof()) {
			std::getline(archivo, aux);
			if (formatoCorrecto(aux)) {
				std::string nombre = aux.substr(aux.find_first_of(SEPARADOR) - 1);
				std::string atributo = aux.substr(aux.find_first_of(SEPARADOR) + 1);
				if (nombre.size() && atributo.size())
					atributos[nombre] = atributo;
			}
		}
	}
	archivo.close();
}

ArchivoConfiguracion::~ArchivoConfiguracion() {}
