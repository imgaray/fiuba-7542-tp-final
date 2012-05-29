/*
 * ArchivoDeDatos.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef ARCHIVODEDATOS_H_
#define ARCHIVODEDATOS_H_

#include <string>
#include <fstream>

typedef unsigned int Id_Registro;

class ArchivoDeDatos {
public:
	ArchivoDeDatos(const std::string& ruta);
	virtual ~ArchivoDeDatos();

	/*
	 * Obtiene el registro con numero "id" del archivo
	 */
	std::string obtenerRegistro(Id_Registro id);

	/*
	 * Guarda el registro en el archivo
	 */
	void guardarRegistro(const std::string& registro);

private:
	std::fstream _archivo;
	Id_Registro _ultimoID;
};

#endif /* ARCHIVODEDATOS_H_ */
