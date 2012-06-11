#include "Consultante.h"
#include "Respuesta.h"
#include <iostream>
#include "Consulta.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;
}

Consultante::~Consultante() {}

void Consultante::hacerConsulta() {
    if (esperandoRespuesta)
        // cancelar
        std::cout << "Consulta anterior cancelada" << std::endl;
    esperandoRespuesta = true;
}

void Consultante::recibirRespuesta(const Respuesta& rta) {
    procesarRespuesta(rta);
    esperandoRespuesta = false;
}

unsigned Consultante::getID() const {
    return ID;
}
