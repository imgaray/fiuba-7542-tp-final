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
//    server.enviarConsulta(this, consulta);
    esperandoRespuesta = true;
    padre->informarConsultaIniciada();
    correrSpinner();
}

void Consultante::cancelarConsulta(ServidorRemoto& server) {
    if (esperandoRespuesta) {
//        server.cancelarConsulta(ID);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

void Consultante::recibirRespuesta(const Respuesta& rta) {
    if (esperandoRespuesta) {
        procesarRespuesta(rta);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

unsigned Consultante::getID() const {
    return ID;
}
