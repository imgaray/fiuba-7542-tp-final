#ifndef EXCEPCION_FILTRADOR_EXISTENTE_H
#define EXCEPCION_FILTRADOR_EXISTENTE_H

#include <exception>
#include <string>

class ExcepcionFiltradorExistente : public std::exception {
    public:
        ExcepcionFiltradorExistente(const std::string& _msj) :
            msj ("La consulta ya está siendo filtrada por ") {
            msj += _msj;
        }

        ~ExcepcionFiltradorExistente() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_FILTRADOR_EXISTENTE_H
