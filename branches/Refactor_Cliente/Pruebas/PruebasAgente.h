/*
 * PruebasAgente.h
 *
 *  Created on: 10/06/2012
 *      Author: migue
 */

#ifndef PRUEBASAGENTE_H_
#define PRUEBASAGENTE_H_

#include <iostream>
#include "../comun/Hilo.h"
#include "../comun/Socket.h"
#include "../comun/Consulta.h"
#include "../comun/Respuesta.h"
using namespace std;

#define PUERTO_PRUEBA_SERVIDOR 4351
#define CANT_CONSULTA 7

class mServidor : public Hilo {
public:
	mServidor() : _sck((Puerto)PUERTO_PRUEBA_SERVIDOR) {
		cout << "Se instancia el Servidor" << endl;
	}

	virtual void correr() {
		_sck.enlazar();
		cout << "Servidor-socket enlazado" << endl;
		Socket *nsck;
		nsck = _sck.escucharConexion();

		if (nsck != NULL)
			cout << "Servidor-conexion Establecida" << endl;


		Consulta crec;

		for (int i = 0; i < 7 ; i++) {
			nsck->recibir(crec);
			cout << endl << "Consulta N°" << i <<" Recibida." << endl;
			cout << "Campos: ";
			for (unsigned j = 0; j < crec.cantidadCampos() ; j++) {
				cout.width(10);
				cout.fill(' ');
				cout << crec.campo(j);
				cout << "|";
			}

			if (i == 4) {
				nsck->enviar(Respuesta(":::CONSULTA RECIBIDA OK:::(ServidoR)"));
			}

			cout << endl;
			crec.limpiar();

		}


		cout << "Servidor-Paquete recibido: ";
		cout << crec.serializar() << endl;

		nsck->desconectar();
		delete nsck;
	}
	~mServidor(){}
	Socket _sck;
};


void testAgenteCargaConfig();
void testAgenteSimple();
void testAgenteCargaDesdeArchivo();


#endif /* PRUEBASAGENTE_H_ */
