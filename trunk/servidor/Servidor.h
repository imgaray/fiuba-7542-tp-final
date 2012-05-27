/*
 * Servidor.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

class Servidor {
private:
	IntermediarioServidor intermediario;
	
public:
	void comenzar();
	void detener();
	void persistir();
	Servidor();
	virtual ~Servidor();
};

#endif /* SERVIDOR_H_ */
