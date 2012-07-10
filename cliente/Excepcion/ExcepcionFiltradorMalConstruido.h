#ifndef EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
#define EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H

#include <exception>
#include <string>

/** @class ExcepcionFiltradorMalConstruido
 * Excepción lanzada cuando sucede alguna de estas cosas:
 * -el campo del filtrador no es un campo válido
 * -alguno de los parámetros auxiliares está erróne
 * -se intentaron agregar dimensiones como resultado luego de definiar que era
 * una consulta de tabla pivote.
 */
class ExcepcionFiltradorMalConstruido : public std::exception {
    public:
        /**
         * Constructor.
         * @param _msj explicación del error
         */
        ExcepcionFiltradorMalConstruido(const std::string& _msj) : msj(_msj) {}

        /**
         * Destructor.
         */
        ~ExcepcionFiltradorMalConstruido() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_FILTRADOR_MAL_CONSTRUIDO_H
