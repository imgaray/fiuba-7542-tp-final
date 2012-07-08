/*
 * pruebaSocket.h
 *
 *  Created on: 06/06/2012
 *      Author: migue
 */

#ifndef PRUEBASOCKET_H_
#define PRUEBASOCKET_H_

#include "Hilo.h"
#include "Socket.h"
#include "Definiciones.h"

class mCliente : public Hilo {
public:
	mCliente(std::string h);
	virtual void correr();
	~mCliente();
private:
	std::string huesped;
	Socket _sck;
};



class mServidor : public Hilo {
public:
	mServidor();
	virtual void correr();
	~mServidor();
private:
	Socket _sck;
};


/**
 * @brief test que comprueba que se envien resciban y envian mensajes
 * correctamente a travez de sockets. Se comprueba principal el
 * correcto funcionamiento del socket.
 */
void testSocket();

#endif /* PRUEBASOCKET_H_ */
