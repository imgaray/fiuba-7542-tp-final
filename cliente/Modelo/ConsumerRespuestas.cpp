#include "ConsumerRespuestas.h"
#include "Consultante.h"
#include "Consulta.h"
#include "Respuesta.h"
#include <iostream>

void ConsumerRespuesta::correr() {
	while (corriendo()) {
		try {
			std::cout << "estoy en el consumer respuesta" << std::endl;
			ParRespuesta prespuesta = respuestas.pop2();
			consultantes[prespuesta.first]->recibirRespuesta(Respuesta(*prespuesta.second));
			delete prespuesta.second;
		} catch (...){
			std::cout << "detuve el consumer respuesta" << std::endl;
			parar();
		}
	}
}

ConsumerRespuesta::ConsumerRespuesta(ColaRespuestas& cresp, MapaConsultantes& mcons):
	respuestas(cresp), consultantes(mcons) {
}

ConsumerRespuesta::~ConsumerRespuesta() {
	std::cout << "entro al destructor de consumer consulta" << std::endl;
}
