/*
 * Utilitario.cpp
 *
 *  Created on: 30/05/2012
 *      Author: migue
 */

#include "Utilitario.h"
#include <vector>

std::vector<size_t> Utilitario::_posiciones;
std::string Utilitario::s_anterior;

Utilitario::Utilitario() {
	// TODO Auto-generated constructor stub

}

Utilitario::~Utilitario() {
	// TODO Auto-generated destructor stub
}


std::string Utilitario::separar(const std::string& datos,
		const char separador, const size_t indice) {
	size_t pos_sep = -1;
	size_t cant_sep = 0;

	if (s_anterior != datos) {
		_posiciones.clear();
		s_anterior = datos;
		bool hayMasSeparadores = true;
		while (hayMasSeparadores) {
			pos_sep = datos.find(separador, pos_sep + 1);

			if (pos_sep != std::string::npos) {
				_posiciones.push_back(pos_sep);
				cant_sep++;
			}
			else{
				hayMasSeparadores = false;
			}
		}
	}

	// si no tiene separadores retorna le dato entero para "indice" = 0
	if ((_posiciones.size() == 0) && (indice == 0)) {
		return datos;
	}

	if (_posiciones.size() > 0 && _posiciones.size() >= indice) {
		std::string arg;
		if (indice == 0) {
			arg = datos;
			arg.resize(_posiciones[0]);
		}
		else {
			arg = &datos.c_str()[_posiciones[indice - 1] + 1];
		}

		// caso para el ultimo argumento
		if (indice == _posiciones.size())
			arg.resize(datos.size() - _posiciones[indice - 1] - 1);
		else if (indice > 0)
			arg.resize(_posiciones[indice] - _posiciones[indice - 1] - 1);

		return arg;
	}
	else {
		// retorno string nulo si indice > cantArgumentos
		return "";
	}
}
