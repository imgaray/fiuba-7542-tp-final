#include "Consultante.h"
#include "Respuesta.h"
#include <iostream>
#include "Consulta.h"
#include "ServidorRemoto.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;
}

Consultante::~Consultante() {}

void Consultante::hacerConsulta(ServidorRemoto& server) {
    cancelarConsulta(server);

    esperandoRespuesta = true;
    std::cout << this << " consulta ";
    if (verificador.verificarConsulta(consulta))
        std::cout << "OK" << std::endl;
    else
        std::cout << "NO OK" << std::endl;

    server.enviarConsulta(this, consulta);
    padre->informarConsultaIniciada();
    correrSpinner();
}

void Consultante::cancelarConsulta(ServidorRemoto& server) {
    if (esperandoRespuesta) {
        server.cancelarConsulta(ID);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

void Consultante::recibirRespuesta(const Respuesta& rta) {
   std::cout << "entre al recibir respuesta de consultante" << std::endl;
    if (esperandoRespuesta) {
		std::cout << "entre al if de esperandoRespuesta" << std::endl;
        std::cout << "mensaje interno de respuesta " << rta.mensajeInterno() << std::endl;
        procesarRespuesta(rta);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

unsigned Consultante::getID() const {
    return ID;
}
