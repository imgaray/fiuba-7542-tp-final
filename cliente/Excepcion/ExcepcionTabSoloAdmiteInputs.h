#ifndef EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H
#define EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H

#include <exception>
#include <string>

class ExcepcionTabSoloAdmiteInputs : public std::exception {
    public:
        ExcepcionTabSoloAdmiteInputs(const std::string& _msj) :
            msj ("Sólo se admiten inputs como filtradores que se apliquen"
                 " a toda la pestaña. Se intentó agregar un ") {
            msj += _msj;
        }

        ~ExcepcionTabSoloAdmiteInputs() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};

#endif  // EXCEPCION_TAB_SOLO_ADMITE_INPUTS_H
