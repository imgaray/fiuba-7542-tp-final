/*
 * Mensaje.h
 *
 *  Created on: 29/05/2012
 *      Author: migue
 */

#ifndef MENSAJE_H_
#define MENSAJE_H_

#include <string>

class Respuesta;
class Consulta;

class Mensaje {
public:
	Mensaje();
	virtual std::string serializar() = 0;
	virtual void deserializar(const std::string& datos) = 0;

	virtual bool esRespuesta();
	virtual bool esConsulta();

	virtual Consulta* consulta() = 0;
	virtual Respuesta* respuesta() = 0;

	virtual ~Mensaje();
};

#endif /* MENSAJE_H_ */
