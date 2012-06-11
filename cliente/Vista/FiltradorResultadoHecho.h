#ifndef FILTRADOR_RESULTADO_HECHO_H
#define FILTRADOR_RESULTADO_HECHO_H

#include "FiltradorResultado.h"
#include "Definiciones.h"

class FiltradorResultadoHecho : public FiltradorResultado {
    public:
        FiltradorResultadoHecho(const Glib::ustring& hecho,
                                const Glib::ustring& agregacion);
        virtual ~FiltradorResultadoHecho();
    private:
        Glib::ustring label;
        static Glib::ustring agregPosibles[];
        Agregacion agregacion;
};

#endif  // FILTRADOR_RESULTADO_HECHO_H
