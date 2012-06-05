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
	static std::string separar(const std::string& datos,
			const char separador, const size_t indice);

	static std::string convertirAString(const int& numero);

	static int convertirAEntero(const std::string& numero);

private:
	Utilitario();
	virtual ~Utilitario();
	static std::vector<size_t> _posiciones;
	static std::string s_anterior;
};

#endif /* UTILITARIO_H_ */
