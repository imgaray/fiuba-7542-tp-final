/*
 * PruebaSS.h
 *
 *  Created on: 15/06/2012
 *      Author: migue
 */

#ifndef PRUEBASS_H_
#define PRUEBASS_H_
#include "Hilo.h"
#include "Socket.h"
#include "Consulta.h"
#include "Respuesta.h"
#include <iostream>

using namespace std;

#define PUERTO_DE_CONEX (Puerto) 4000
#define CANT_CONSULTAS_ENVIADAS 5
#define CANT_RESPUESTAS_ENVIDAS 5


/*
 * Cabecera para prueba de serializacion con socket
 */

class ssEmisor : public Hilo {
public:
	ssEmisor(Consulta* cons, Respuesta* resp) : _sck(PUERTO_DE_CONEX){
		_resp = resp;
		_cons = cons;
		errores = 0;
	}
	virtual ~ssEmisor() { }

	virtual void correr() {
		_sck.conectar("localhost");

		if (!_sck.conectado()) {
			cout << "Emi-Se no esta conectado con Receptor"<< endl;
		}

		Consulta c;
		Respuesta r;
		for (unsigned i = 0 ; i < CANT_CONSULTAS_ENVIADAS ; i++) {
			_sck.enviar(_cons[i]);
		}

		for (unsigned i = 0; i < CANT_RESPUESTAS_ENVIDAS ; i++) {
			_sck.enviar(_resp[i]);
		}

		_sck.desconectar();
	}

	int cantErrores() {
		return errores;
	}
	Consulta *_cons;
	Respuesta *_resp;
	Socket _sck;
	int errores;
};

class ssReceptor : public Hilo {
public:
	ssReceptor(Consulta* cons, Respuesta* resp) : _sckEnlazado (PUERTO_DE_CONEX){
		_resp = resp;
		_cons = cons;
		errores = 0;
	}
	virtual ~ssReceptor() { }

	virtual void correr() {
		_sckEnlazado.enlazar();
		Socket *conexion = _sckEnlazado.escucharConexion();

		if (conexion == NULL) {
			cout << "Rec-Conexion con Emisor no establecida: socket NULO" << endl;
		}

		Consulta c;
		Respuesta r;
		for (unsigned i = 0; i < CANT_CONSULTAS_ENVIADAS ; i++) {
			conexion->recibir(c);

			c.deserializar(c.serializar());
			c.deserializar(c.serializar());
			c.deserializar(c.serializar());
			c.deserializar(c.serializar());

			if (c.serializar() != _cons[i].serializar()) {
				cout << endl;
				cout << "Rec-Error con la Consulta " << i << endl;
				cout << "Rec-Orig: " << _cons[i].serializar() << endl;
				cout << "Rec-Rec:  " << c.serializar() << endl;

				errores++;
			}
		}

		for (unsigned i = 0; i < CANT_RESPUESTAS_ENVIDAS ; i++) {
			conexion->recibir(r);

			r.deserializar(r.serializar());
			r.deserializar(r.serializar());
			r.deserializar(r.serializar());
			r.deserializar(r.serializar());

			if (r.serializar() != _resp[i].serializar()) {
				cout << "Error con la Respuesta " << i << endl;
				errores++;
			}
		}


		conexion->desconectar();
		delete conexion;
		_sckEnlazado.desconectar();
	}

	int cantErrores() {
		return errores;
	}

	Socket _sckEnlazado;
	Consulta *_cons;
	Respuesta *_resp;
	int errores;
};


/**
 * @brief test de serializacion por sockets que comprueba que las serializaciones
 * de consultas y respuestas, al enviarlas por sockets se reciban correctamente
 * del lado del receptor y se puedan deserializar estas de forma correcta,
 * con sus atributos correctos. Se comprueba principalmente que haga la correcta
 * recuparacion de consulta y respuestas a travez de sockets.
 */
void testSS();

/*
 * Funciones auxiliares para testSS()
 */
void inicializarConsultas(Consulta* cons);
void inicializarRespuesta(Respuesta* resp);

#endif /* PRUEBASS_H_ */
