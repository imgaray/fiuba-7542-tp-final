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
//		    std::cout << "Recibido en el consumerRespuesta por socket: " << r.second.serializar() << std::endl << "\tID: " << r.second.devolverID() << std::endl,
            if (r.second.mensajeInterno() != Respuesta::mensajeError) {
                r.first = r.second.devolverID();
                if (cancelados.has(r.first) &&
                                    cancelados[r.first]) {
                        cancelados[r.first] = false;
                } else {
                    //std::cout << "Agregando a la cola de respuestas de ConsumerRespuesta respuesta: " << r.second.serializar() << ", de ID: ";
//                    if (r.first == r.second.devolverID())
//                        std:: cout << r.first << std::endl;
                    respuestas.push(r);
                }
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

