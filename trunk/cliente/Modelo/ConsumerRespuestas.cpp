#include "ConsumerRespuestas.h"
#include "Consultante.h"
#include "Consulta.h"
#include "Respuesta.h"

void ConsumerRespuesta::correr() {
	while (corriendo()) {
		try {
			ParRespuesta prespuesta = respuestas.pop2();
			consultantes[prespuesta.first]->recibirRespuesta(Respuesta(*prespuesta.second));
			delete prespuesta.second;
		} catch (...){
			parar();
		}
	}
}

ConsumerRespuesta::ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons):
	respuestas(cresp), consultantes(mcons) {
}

ConsumerRespuesta::~ConsumerRespuesta() {
}
