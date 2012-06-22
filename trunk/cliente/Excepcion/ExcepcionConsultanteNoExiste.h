/*
 * ExcepcionConsultanteNoExiste.h
 *
 *  Created on: 19/06/2012
 *      Author: migue
 */

#ifndef EXCEPCIONCONSULTANTENOEXISTE_H_
#define EXCEPCIONCONSULTANTENOEXISTE_H_

#include <exception>
#include <string>

class ExcepcionConsultanteNoExiste : public std::exception {
    public:
		ExcepcionConsultanteNoExiste(const std::string& _msj) :
            msj ("El Consultante No Existe: ") {
            msj += _msj;
        }

        ~ExcepcionConsultanteNoExiste() throw() {}

        virtual const char* what() const throw() {
            return msj.c_str();
        }
    private:
        std::string msj;
};


#endif /* EXCEPCIONCONSULTANTENOEXISTE_H_ */
