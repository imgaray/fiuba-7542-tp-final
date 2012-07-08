/*
 * Mensaje.h
 *
 *  Created on: 29/05/2012
 *      Author: migue
 */

#ifndef MENSAJE_H_
#define MENSAJE_H_

#include <string>

/**
 * @class Mensaje
 * 	Esta clase es abstracta y representa a la comunicacion habra entre un
 * cliente con un servidor o un agente con un servidor.
 */

class Mensaje {
public:
	/**
	 * @brief Constructor sin Argumentos.
	 */
	Mensaje();
	virtual ~Mensaje();

	/**
	 * @brief Metodo que serializa todo el mensaje en un string
	 * @return string con el mensjae serializado.
	 */
	virtual std::string serializar() const = 0;

	/**
	 * @brief Metodo que se deserialza a partir de un string.
	 * @param datos string que contiene el Mensaje serializado.
	 */
	virtual void deserializar(const std::string& datos) = 0;
};

#endif /* MENSAJE_H_ */
