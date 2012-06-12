#ifndef _ARCHIVOCONFIGURACION_H
#define _ARCHIVOCONFIGURACION_H

#include <fstream>
#include <string>
#include <map>
#define RUTA "archivo.configuracion"

class ArchivoConfiguracion {
private:
	std::string rutaArchivo;
	std::map<std::string, std::string> atributos;
	bool formatoCorrecto(std::string& linea);
public:
	typedef std::map<std::string, std::string>::iterator iterator;
	std::string obtenerAtributo(std::string& name);
	iterator begin();
	iterator end();
	explicit ArchivoConfiguracion(char* ruta = RUTA);
	~ArchivoConfiguracion();

};

#endif
