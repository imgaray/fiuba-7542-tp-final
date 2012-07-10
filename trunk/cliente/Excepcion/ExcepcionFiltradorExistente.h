#ifndef EXCEPCION_FILTRADOR_EXISTENTE_H
#define EXCEPCION_FILTRADOR_EXISTENTE_H

#include <exception>
#include <string>

/** @class ExcepcionFiltradorExistente
 * Excepción lanzada cuando se intenta agregar un filtrador sobre un campo que
 * ya existía.
 */
class ExcepcionFiltradorExistente : public std::exception {
    public:
        /**
         * Constructor.
         * @param _msj campo repetido
         */
        ExcepcionFiltradorExistente(const std::string& _msj) :
            msj ("La consulta ya está siendo filtrada por ") {
            msj += _msj;
        }

        /**
         * Destructor.
         */
        ~ExcepcionFiltradorExistente() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_FILTRADOR_EXISTENTE_H
