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
#include "Consulta.h"
#include <iostream>
#include <stdlib.h>

#define PUERTO 4322
using namespace std;

class mCliente : public Hilo {
public:
	mCliente(std::string h) : _sck((Puerto)PUERTO) {
		this->huesped = h;
	}

	virtual void correr() {
		cout <<"Cliente-inicia el hilo"<< endl;


		Consulta c;
		c.agregarFiltro("FILTRO", "ValorFiltro");
		c.agregarResultado("HOLA HOLA");

		//_sck.enviar(c);

		_sck.conectar(this->huesped);
		cout << "Cliente-conexion establecida" << endl;

		cout << "CLiente-paquete a enviar:  " << c.serializar() << endl;
		_sck.enviar(c);
		cout << "Cliente-Paquete Enviado" << endl;


		_sck.desconectar();
	}



	~mCliente(){}
	std::string huesped;
	Socket _sck;
};


class mServidor : public Hilo {
public:
	mServidor() : _sck((Puerto)PUERTO) {

	}



	virtual void correr() {
		_sck.enlazar();
		cout << "Servidor-socket enlazado" << endl;
		Socket *nsck;
		nsck = _sck.escucharConexion();

		if (nsck != NULL)
			cout << "Servidor-conexion Establecida" << endl;


		Consulta crec;
		nsck->recibir(crec);

		cout << "Servidor-Paquete recibido: ";
		cout << crec.serializar() << endl;

		nsck->desconectar();
		delete nsck;
	}
	~mServidor(){}
	Socket _sck;
};

/**
 * @brief test que comprueba que se envien resciban y envian mensajes
 * correctamente a travez de sockets. Se comprueba principal el
 * correcto funcionamiento del socket.
 */
void testSocket() {
	cout << endl;
	cout << "Inicia test para Socket" << endl;
	mServidor servidor;
	mCliente cliente("localhost");

	servidor.iniciar();

	sleep(3);

	cliente.iniciar();

	servidor.sincronizar();
	cliente.sincronizar();


	cout << endl;
	cout << "Finaliza test para socket" << endl;
	cout << endl;
}


#endif /* PRUEBASOCKET_H_ */
