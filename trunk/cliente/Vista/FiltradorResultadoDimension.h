#ifndef FILTRADOR_RESULTADO_DIMENSION_H
#define FILTRADOR_RESULTADO_DIMENSION_H

#include "FiltradorResultado.h"

class FiltradorResultadoDimension : public FiltradorResultado {
    public:
        FiltradorResultadoDimension(const Glib::ustring& resultado);
        virtual ~FiltradorResultadoDimension();

        Consulta& filtrar(Consulta& c);

        Glib::ustring pertenece(const Glib::ustring& valor);
};

#endif  // FILTRADOR_RESULTADO_DIMENSION_H
