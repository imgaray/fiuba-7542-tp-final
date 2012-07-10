#ifndef FILTRADOR_RESULTADO_DIMENSION_H
#define FILTRADOR_RESULTADO_DIMENSION_H

#include "FiltradorResultado.h"

/** @class FiltradorResultadoDimension
 * Resultado de comportamiento "básico", es decir, no es hecho ni fecha.
 */
class FiltradorResultadoDimension : public FiltradorResultado {
    public:
        FiltradorResultadoDimension(const Glib::ustring& resultado);
        virtual ~FiltradorResultadoDimension();

        void filtrar(Consulta& c);
};

#endif  // FILTRADOR_RESULTADO_DIMENSION_H
