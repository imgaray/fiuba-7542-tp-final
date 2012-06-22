#ifndef EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H
#define EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H

#include <exception>
#include <string>

class ExcepcionArchivoGladeCorrupto : public std::exception {
    public:
        ExcepcionArchivoGladeCorrupto(const std::string& _msj) :
            msj ("Error en el archivo de GLADE. No encontrado: ") {
            msj += _msj;
        }

        ~ExcepcionArchivoGladeCorrupto() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H
