/*
 * PruebaCCS.h
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#ifndef PRUEBACCS_H_
#define PRUEBACCS_H_

#include <iostream>
#include "Hilo.h"
#include "Socket.h"
#include "GenRegistros.h"
#include "Consulta.h"
#include "Respuesta.h"
#include "Definiciones.h"
#include "BaseDeDatos.h"

using namespace std;

#define P_SERVIDOR	(Puerto) 4000
#define P_CLIENTE	(Puerto) 4000

#define PUERTO_CONEX (Puerto) 4000

void imprimirRes(const Respuesta& resp);


class ccsServidor : public Hilo {
public:
	ccsServidor() :  _sckEnlace(PUERTO_CONEX), bdd("rutaDatosCCS.txt") {
		//bdd.borrarDatos();
		generarRegistros(bdd,100);
		_sckEnlace.enlazar();
	}
	~ccsServidor() {}

	virtual void correr() {
		Socket* nsocket;
		Consulta c;
		Respuesta r;

		nsocket = _sckEnlace.escucharConexion();

		if (nsocket == NULL) {
			cout << "************SOCKET NULO" << endl;
		}

		nsocket->recibir(c);
		r = bdd.resolverConsulta(c);

		nsocket->enviar(r);
	}


private:
	Socket _sckEnlace;
	BaseDeDatos bdd;
};


class ccsCliente : public Hilo {
public:
	ccsCliente() : _sck(PUERTO_CONEX){
		_sck.conectar("localhost");
	}
	virtual ~ccsCliente() {}

	virtual void correr() {
		Consulta c;
		Respuesta r;
		c.definirComoConsultaCliente();
		c.agregarResultado("Vendedor");
		c.defininirAgregacion(SUM, Organizacion::nombreHecho(0));
		//c.agregarResultado("Sucursal");

		_sck.enviar(c);
		_sck.recibir(r);

		imprimirRes(r);

		_sck.desconectar();
	}

	Socket _sck;
};

/**
 * @brief test para "Consulta Cliente con Servidor" que comprueba que se
 * resuelvan correctamente consultas con corriendo un cliente y un
 * servidor en dos hilos separados. Se comprueba la correcta recepcion
 * de consulta resuelta a travez de un respuesta.
 */
void testCCS();

#endif /* PRUEBACCS_H_ */
