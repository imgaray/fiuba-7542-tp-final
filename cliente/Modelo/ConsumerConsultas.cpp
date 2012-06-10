#include "ConsumerConsultas.h"

void ConsumerConsulta::detener_hilo() {
	servidor->desconectar();
	parar();
}

void ConsumerConsulta::correr() {
	while (corriendo()) {
		if (servidor && servidor->conectado()) {
			try {
				bool error = false;
				ParConsulta pconsulta = consultas.pop2();
				ParRespuesta parrta;
				parrta.first = pconsulta.first;
				parrta.second = new Respuesta();
				if (servidor->enviar(*pconsulta.second)) { 
					error = servidor->recibir(*parrta.second);
				}
				delete pconsulta.second;
				if (error) {
					detener_hilo();
				} else {
					respuestas.push(parrta);
				}
			} catch(...) {
				detener_hilo();
			}
		}
	}
}

ConsumerConsulta::ConsumerConsulta(ColaConsultas& cons, ColaRespuestas& resp):
	consultas(cons), respuestas(resp) {
	// TODO: terminar este constructor
	servidor = new Socket(PORT_CLIENTE);
	servidor->conectar(SHOST);
}

ConsumerConsulta::~ConsumerConsulta() {
	if (corriendo())
		detener_hilo();
	delete servidor;
}
