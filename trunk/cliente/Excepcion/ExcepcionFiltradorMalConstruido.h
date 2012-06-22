#ifndef EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
#define EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H

#include <exception>
#include <string>

class ExcepcionFiltradorMalConstruido : public std::exception {
    public:
        ExcepcionFiltradorMalConstruido(const std::string& _msj) : msj(_msj) {}

        ~ExcepcionFiltradorMalConstruido() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
