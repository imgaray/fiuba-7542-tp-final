#include "ConsumerRespuestas.h"
#include "Consultante.h"
#include "Consulta.h"
#include "Respuesta.h"
#include <iostream>
#include "BLQueue.h"

void ConsumerRespuesta::correr() {
	while (corriendo()) {
		ParRespuesta r;
		if (servidor->recibir(r.second)) {
			r.first = r.second.devolverID();
			if (cancelados.has(r.first) && 
								cancelados[r.first]) {
					cancelados[r.first] = false;
			} else {
				std::cout << "recibi una respuesta para el id " << r.first << std::endl;
				std::cout << "serializacion = " << r.second.serializar() << std::endl;
				respuestas.push(r);
			}
		} else {
			parar();
		}
	}
}

ConsumerRespuesta::ConsumerRespuesta(ColaRespuestas& cresp,
			MapaConsultantes& mcons, Socket*& conex, BitmapCancelados& canc):
		respuestas(cresp),
		consultantes(mcons),
		servidor(conex),
		cancelados(canc) {
	
}

ConsumerRespuesta::~ConsumerRespuesta() {
	parar();
}