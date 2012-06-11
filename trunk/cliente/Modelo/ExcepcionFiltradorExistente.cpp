#include "ExcepcionFiltradorExistente.h"
#include <cstring>

ExcepcionFiltradorExistente::ExcepcionFiltradorExistente(const char* _msj) {
    strcpy(msj, "La consulta ya está siendo filtrada por ");
    strcpy(msj+strlen(msj), _msj);
}

const char* ExcepcionFiltradorExistente::what() const throw() {
    return msj;
}

