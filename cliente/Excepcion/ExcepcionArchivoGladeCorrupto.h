#ifndef EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H
#define EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H

#include <exception>
#include <string>

/** @class ExcepcionArchivoGladeCorrupto
 * Excepción lanzada cuando no se encuentra un widget con cierto nombre en el
 * archivo de GLADE.
 */
class ExcepcionArchivoGladeCorrupto : public std::exception {
    public:
        /**
         * Constructor.
         * @param _msj aquello que no fue encontrado
         */
        ExcepcionArchivoGladeCorrupto(const std::string& _msj) :
            msj ("Error en el archivo de GLADE. No encontrado: ") {
            msj += _msj;
        }

        /**
         * Destructor.
         */
        ~ExcepcionArchivoGladeCorrupto() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_ARCHIVO_GLADE_CORRUPTO_H
