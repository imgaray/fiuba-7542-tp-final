#include "Consultante.h"
#include "Respuesta.h"
#include <iostream>
#include "Consulta.h"
#include "ServidorRemoto.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;

    std::cout << "Consultante creado "<< ID+1 << "/" << generadorID << std::endl;
}

Consultante::~Consultante() {}

void Consultante::hacerConsulta(ServidorRemoto& server) {
    cancelarConsulta(server);

//    server.enviarConsulta(this, consulta);
    std::cout << "Consultante "<< ID+1 << "/" << generadorID
              << ". Consulta realizada, esperando respuesta" << std::endl;
    esperandoRespuesta = true;
}

void Consultante::cancelarConsulta(ServidorRemoto& server) {
    if (esperandoRespuesta) {
//        server.cancelarConsulta(ID);
        padre->informarConsultaTerminada();
        std::cout << "Consulta anterior cancelada" << std::endl;
        esperandoRespuesta = false;
    }
}

void Consultante::recibirRespuesta(const Respuesta& rta) {
    if (esperandoRespuesta) {
        procesarRespuesta(rta);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
    }
}

unsigned Consultante::getID() const {
    return ID;
}
