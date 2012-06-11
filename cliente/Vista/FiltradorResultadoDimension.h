#ifndef FILTRADOR_RESULTADO_DIMENSION_H
#define FILTRADOR_RESULTADO_DIMENSION_H

#include "FiltradorResultado.h"

class FiltradorResultadoDimension : public FiltradorResultado {
    public:
        FiltradorResultadoDimension(const Glib::ustring& resultado);
        virtual ~FiltradorResultadoDimension();
};

#endif  // FILTRADOR_RESULTADO_DIMENSION_H
