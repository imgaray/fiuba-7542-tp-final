#include "ExcepcionFiltradorMalConstruido.h"
#include <cstring>

ExcepcionFiltradorMalConstruido::ExcepcionFiltradorMalConstruido(
    const char* _msj) {
    strcpy(msj, _msj);
}

const char* ExcepcionFiltradorMalConstruido::what() const throw() {
    return msj;
}
