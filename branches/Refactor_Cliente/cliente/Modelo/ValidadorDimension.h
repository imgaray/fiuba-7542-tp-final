#ifndef VALIDADOR_DIMENSION_H
#define VALIDADOR_DIMENSION_H

#include "Validador.h"

class ValidadorDimension : public Validador {
    public:
        ValidadorDimension(char tipo, const Glib::ustring& nombre,
                           bool admiteNumeros);

        Campos getCampos(unsigned i = 0);

        Glib::ustring validar(Campos& acotados, Campos& noAcotados);

        Glib::ustring validar(Glib::ustring& acotado,
                              Glib::ustring& noAcotado);

        Campos getEstadoNoAcotados(Campos& acotados);
        Glib::ustring getEstadoNoAcotados(Glib::ustring& acotado);
    private:
        bool admiteNumeros;
};

#endif  // VALIDADOR_DIMENSION_H
