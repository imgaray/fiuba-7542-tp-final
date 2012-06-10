#ifndef __CONSUMERCONSULTAS_H
#define __CONSUMERCONSULTAS_H

#include "Socket.h"
#include "Definiciones.h"

class ConsumerConsulta: public Hilo {
private:
	Socket* servidor;
	ColaConsultas& consultas;
	ColaRespuestas& respuestas;
public:
	void detener_hilo() {
		servidor->desconectar();
		parar();
	}
	void correr() {
		while (corriendo()) {
			if (servidor && servidor->conectado()) {
				bool error = true;
				ParConsulta pconsulta = consultas.pop2();
				ParRespuesta prespuesta;
				prespuesta.second = pconsulta.first;
				if (servidor->enviar(pconsulta.second)) 
					error = servidor->recibir(prespuesta.second);
				if (error) {
					detener_hilo();
				} else {
					respuestas.push(prespuesta);
				}
			}
		}
	}
	ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp):
		consultas(cons), respuestas(resp) {
		// TODO: terminar este constructor
//		servidor = new Socket();
	}
	~ConsumerConsulta() {
		if (corriendo())
			detener_hilo();
		delete servidor;
	}
};

#endif
