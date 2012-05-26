/*
 * BaseDeDatos.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

class Respuesta;
class Consulta;

class BaseDeDatos {
public:
	BaseDeDatos();

	Respuesta resolverConsulta(const Consulta& consulta);

	/*
	 * Agrega una entrada por parte del agente
	 */
	Respuesta agregarEntrada(const Consulta& entrada);
	virtual ~BaseDeDatos();
};

#endif /* BASEDEDATOS_H_ */
