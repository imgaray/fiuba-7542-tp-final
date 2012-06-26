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
#include "Mutex.h"

typedef unsigned int Id_Registro;

/*
 * @DOC:
						Clase ArchivoDeDatos

	Esta clase es la encargada de almacenar todo tipo de registros guardandolos
	en disco, permitiendo acceder a estos a partir de su id de registro.

Atributos:

	fstream _archivoPrincipal: stream que contiene los registros de tamanio variable
	en disco.
*
	fstream _posRelativas: stream que contiene las posiciones relativas de los registros
	del _archivoPrincipal.
*
	Id_Registro _ultimoID: variable numerica que representa la cantidad de registros que
	se encuentran almacenados.
*
	std::string _rutaArchivoPrin: string que guarda la ruta del archivo principal en disco.
*
	std::string _rutaArchivoSec: string que guarda la ruta del archivo de posiciones relativas.
*
	Mutex _mutex: utilizado para bloquear el acceso a disco para hacer la clase "Thread Safe".

 * @END
 * */



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
	Id_Registro guardarRegistro(const std::string& registro);

	/*
	 * Retorna la cantidad de registros que estan guardados en el archivo
	 */
	size_t cantidadRegistros() const;

	/*
	 * Borra todo el contenido de los datos
	 */

	void borrarDatos();

private:
	/*
	 * Lee un registro desde el argumento posicion y lo almacena en
	 * el otro argumento string reg.
	 */
	void leerRegistro(const size_t& posicion, std::string& reg);

	/*
	 * Inicializa los archivos utilizados de la Clase
	 */
	void inicilizarArchivos();

	std::fstream _archivoPrincipal;
	std::fstream _posRelativas;
	Id_Registro _ultimoID;

	std::string _rutaArchivoPrin;
	std::string _rutaArchivoSec;

	Mutex _mutex;
};

#endif /* ARCHIVODEDATOS_H_ */
