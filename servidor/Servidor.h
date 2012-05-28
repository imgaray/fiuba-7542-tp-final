/*
 * Servidor.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_
#include "BaseDeDatos.h"
#include "IntermediarioServidor.h"


class Servidor {
private:
	BaseDeDatos bdd;
	IntermediarioServidor intermediario;
	VerificadorConsultas verificador;
	
public:
	
	void comenzar();
	void detener();
	void persistir();
	Servidor();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
