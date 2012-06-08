#include "Consultante.h"
#include "../../comun/Respuesta.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;
}

