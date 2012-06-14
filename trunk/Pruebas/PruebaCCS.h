/*
 * PruebaCCS.h
 *
 *  Created on: 12/06/2012
 *      Author: migue
 */

#ifndef PRUEBACCS_H_
#define PRUEBACCS_H_

#include <iostream>
#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/GenRegistros.h"
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"
#include "../comun/Definiciones.h"
#include "../servidor/MotorDeConsultas/BaseDeDatos.h"

using namespace std;

#define P_SERVIDOR	(Puerto) 4000
#define P_CLIENTE	(Puerto) 4000

#define PUERTO_CONEX (Puerto) 4000

void imprimirRes(const Respuesta& resp);


class ccsServidor : public Hilo {
public:
	ccsServidor() : bdd("rutaDatosCCS.txt"), _sckEnlace(PUERTO_CONEX){
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

		nsocket;
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


void testCCS();

#endif /* PRUEBACCS_H_ */
