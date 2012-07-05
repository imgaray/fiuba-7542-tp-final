#ifndef FILTRADOR_RESULTADO_HECHO_H
#define FILTRADOR_RESULTADO_HECHO_H

#include "FiltradorResultado.h"
#include "Definiciones.h"

class FiltradorResultadoHecho : public FiltradorResultado {
    public:
        FiltradorResultadoHecho(const Glib::ustring& hecho,
                                const Glib::ustring& agregacion);
        virtual ~FiltradorResultadoHecho();

        void filtrar(Consulta& c);

    private:
        int i;
        Glib::ustring hecho;
        Agregacion agregacion;
};

#endif  // FILTRADOR_RESULTADO_HECHO_H
