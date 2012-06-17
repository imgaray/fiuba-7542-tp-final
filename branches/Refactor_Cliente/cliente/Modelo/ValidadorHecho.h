#ifndef VALIDADOR_HECHO_H
#define VALIDADOR_HECHO_H

#include "Validador.h"

class ValidadorHecho : public Validador {
    public:
        ValidadorHecho(char tipo, const Glib::ustring& nombre);

        Campos getCampos(unsigned i = 0);

        Glib::ustring validar(Campos& acotados, Campos& noAcotados);

        Glib::ustring validar(Glib::ustring& acotado,
                              Glib::ustring& noAcotado);

        Campos getEstadoNoAcotados(Campos& acotados);
        Glib::ustring getEstadoNoAcotados(Glib::ustring& acotado);
};

#endif  // VALIDADOR_HECHO_H
