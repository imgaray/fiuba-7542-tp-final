/*
 * ArchivoDeDatos.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef ARCHIVODEDATOS_H_
#define ARCHIVODEDATOS_H_

#include "Definiciones.h"
#include <string>

class ArchivoDeDatos {
public:
	ArchivoDeDatos(const std::string& ruta);
	virtual ~ArchivoDeDatos();

	/*
	 * Obtiene el registro con numero "id" del archivo
	 */
	std::string obtenerRegistro(Id_Registro id);

	/*
	 *
	 */
	void guardarRegistro(const std::string& registro);

private:
	std::fstream _archivo;
	Id_Registro _ultimo_id;
};

#endif /* ARCHIVODEDATOS_H_ */
