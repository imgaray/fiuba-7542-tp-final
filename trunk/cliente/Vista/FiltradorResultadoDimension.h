#ifndef FILTRADOR_RESULTADO_DIMENSION_H
#define FILTRADOR_RESULTADO_DIMENSION_H

#include "FiltradorResultado.h"

/** @class FiltradorResultadoDimension
 * Resultado de comportamiento "básico", es decir, no es hecho ni fecha.
 */
class FiltradorResultadoDimension : public FiltradorResultado {
    public:
        /**
         * Constructor.
         * @param resultado nombre del campo
         */
        FiltradorResultadoDimension(const Glib::ustring& resultado);
        /**
         * Destructor.
         */
        virtual ~FiltradorResultadoDimension();

        /**
         * Agrega el resultado a la consulta.
         * @param c consulta
         */
        void filtrar(Consulta& c);
};

#endif  // FILTRADOR_RESULTADO_DIMENSION_H
