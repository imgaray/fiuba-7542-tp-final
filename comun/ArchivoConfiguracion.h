#ifndef _ARCHIVOCONFIGURACION_H
#define _ARCHIVOCONFIGURACION_H

#include <fstream>
#include <string>
#include <map>
#define RUTA "archivo.configuracion"

class ArchivoConfiguracion {
private:
	std::map<std::string, std::string> atributos;
	bool formatoCorrecto(std::string& linea);
public:
	std::string obtenerAtributo(std::string& name);
	explicit ArchivoConfiguracion(char* ruta = RUTA);
	~ArchivoConfiguracion();

};

#endif
