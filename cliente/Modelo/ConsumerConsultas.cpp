#include "ConsumerConsultas.h"
#include <sstream>
#include <iostream>
#include "BLQueue.h"

void ConsumerConsulta::correr() {
	while (corriendo()) {
		if (servidor && servidor->conectado()) {
			try {
				ParConsulta pconsulta = consultas.pop2();
				if (cancelados.has(pconsulta.first) && 
								cancelados[pconsulta.first]) {
					cancelados[pconsulta.first] = false;
				} else {
					if (!servidor->enviar(pconsulta.second))
						parar();
					std::cout << "envie una consulta para el id " << pconsulta.first << std::endl;
					std::cout << "serializacion = " << pconsulta.second.serializar() << std::endl;
				}
			} catch(BLQueueException& e) {
				parar();
			}
		}
	}
}

ConsumerConsulta::ConsumerConsulta(ColaConsultas& cons,
		ColaRespuestas& resp, Socket*& conex, BitmapCancelados& canc):
				consultas(cons),
				respuestas(resp),
				servidor(conex),
				cancelados(canc) {
}

ConsumerConsulta::~ConsumerConsulta() {
	parar();
}
