#include "Consultante.h"
#include "../../comun/Respuesta.h"
#include <iostream>

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;
}

Consultante::~Consultante() {}

void Consultante::hacerConsulta() const {
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
