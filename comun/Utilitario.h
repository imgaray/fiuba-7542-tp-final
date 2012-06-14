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

class Utilitario {
public:
	Utilitario();
	virtual ~Utilitario();
	std::string separar(const std::string& datos,
			const char separador, const size_t indice);

	std::string convertirAString(const int& numero);

	int convertirAEntero(const std::string& numero);

	void borrarCaracter(std::string& palabra, const char caracter);

private:
	std::vector<size_t> _posiciones;
	std::string s_anterior;
};

#endif /* UTILITARIO_H_ */
