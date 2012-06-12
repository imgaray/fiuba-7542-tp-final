#include "ArchivoConfiguracion.h"

#define SEPARADOR '='

std::string ArchivoConfiguracion::obtenerAtributo(std::string& name) {
	std::string ret;
	if (atributos.find(name) != atributos.end()) {
		ret = atributos[name];
	}
	return ret;
}

std::string ArchivoConfiguracion::obtenerAtributo(char* nombre) {
	std::string nm = nombre;
	return obtenerAtributo(nm);
}

ArchivoConfiguracion::iterator ArchivoConfiguracion::begin() {
	return atributos.begin();
}

ArchivoConfiguracion::iterator ArchivoConfiguracion::end() {
	return atributos.end();
}

bool ArchivoConfiguracion::formatoCorrecto(std::string& linea) {
	return (linea.find(SEPARADOR) != std::string::npos && 
	(linea.find_first_of(SEPARADOR) == linea.find_last_of(SEPARADOR)));
}

ArchivoConfiguracion::ArchivoConfiguracion(const char* ruta): rutaArchivo(ruta) {
	std::fstream archivo(ruta);
	if (!archivo) {
		// manejar el caso de primer uso
	} else {
		std::string aux;
		while(!archivo.eof()) {
			std::getline(archivo, aux);
			if (formatoCorrecto(aux)) {
				unsigned int posSeparador = aux.find_first_of(SEPARADOR);
				std::string nombre = aux.substr(0, posSeparador);
				std::string atributo = aux.substr(posSeparador + 1);
				if (nombre.size() && atributo.size())
					atributos[nombre] = atributo;
			}
		}
	}
	archivo.close();
}

ArchivoConfiguracion::~ArchivoConfiguracion() {}
