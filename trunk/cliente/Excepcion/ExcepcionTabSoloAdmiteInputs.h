#ifndef EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H
#define EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H

#include <exception>
#include <string>

/** @class ExcepcionTabSoloAdmiteInputs
 * Excepción lanzada cuando se intenta agregar un filtrador que no es
 * input a los filtradores de la pestaña.
 */
class ExcepcionTabSoloAdmiteInputs : public std::exception {
    public:
        /**
         * Constructor.
         * @param _msj aquello que se intentó agregar y provocó la excepción
         */
        ExcepcionTabSoloAdmiteInputs(const std::string& _msj) :
            msj ("Sólo se admiten inputs como filtradores que se apliquen"
                 " a toda la pestaña. Se intentó agregar un ") {
            msj += _msj;
        }

        /**
         * Destructor.
         */
        ~ExcepcionTabSoloAdmiteInputs() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H
