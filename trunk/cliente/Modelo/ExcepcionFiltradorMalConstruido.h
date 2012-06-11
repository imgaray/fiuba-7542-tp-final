#ifndef EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
#define EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H

#include <exception>

class ExcepcionFiltradorMalConstruido : public std::exception {
    public:
        ExcepcionFiltradorMalConstruido(const char* msj);
        virtual const char* what() const throw();
    private:
        char msj[160];
};

#endif  // EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
