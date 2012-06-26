/*
 * Mensaje.h
 *
 *  Created on: 29/05/2012
 *      Author: migue
 */

#ifndef MENSAJE_H_
#define MENSAJE_H_

#include <string>

/*
 * @DOC:
						Clase Mensaje

	Esta clase es abstracta y representa a la comunicacion habra entre un cliente con
	un servidor o un agente con un servidor.

 * @END
 * */

class Mensaje {
public:
	Mensaje();
	virtual ~Mensaje();

	virtual std::string serializar() const = 0;
	virtual void deserializar(const std::string& datos) = 0;
};

#endif /* MENSAJE_H_ */
