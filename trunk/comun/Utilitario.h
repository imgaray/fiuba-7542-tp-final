/*
 * Separador.h
 *
 *  Created on: 30/05/2012
 *      Author: migue
 */

#ifndef UTILITARIO_H_
#define UTILITARIO_H_
#include <string>
#include "Definiciones.h"

/*
 * @DOC:
						Clase Utilitario

	Esta clase es usada para realizar operaciones auxiliares como separar un
	string en varios, borrar caracterez de un string, convertir un string en entero
	y al reves.

Atributos:
	std::vector<size_t> _posiciones: almacena las posiciones del string donde se encuentra
	el caracter separador.
*
	std::string s_anterior: almacena el string anterior a una separacion, para no tener
	que recalcular las posiciones del caracter separador en el string.
*
	char sep_anterior: almacena el caracter usado para la separacion en la separacion anterior.
 * @END
 * */


class Utilitario {
public:
	Utilitario();
	virtual ~Utilitario();
	std::string separar(const std::string& datos,
			const char separador, const size_t indice);

	std::string convertirAString(const int& numero) const;

	int convertirAEntero(const std::string& numero) const;

	void borrarCaracter(std::string& palabra, const char caracter);
private:
	std::vector<size_t> _posiciones;
	std::string s_anterior;
	char sep_anterior;
};

#endif /* UTILITARIO_H_ */
