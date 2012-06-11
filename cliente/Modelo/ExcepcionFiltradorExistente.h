#ifndef EXCEPCION_FILTRADOR_EXISTENTE_H
#define EXCEPCION_FILTRADOR_EXISTENTE_H

#include <exception>

class ExcepcionFiltradorExistente : public std::exception {
    public:
        ExcepcionFiltradorExistente(const char* msj);
        virtual const char* what() const throw();
    private:
        char msj[80];
};

#endif  // EXCEPCION_FILTRADOR_EXISTENTE_H
