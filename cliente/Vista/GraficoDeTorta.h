#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

/** @class GraficoDeTorta
 * Consultante que muestra sus resultados como un gráfico de torta.
 */
class GraficoDeTorta : public Grafico {
    public:
        /**
         * Constructor.
         * @param f filtradores del panel
         */
        GraficoDeTorta(FiltradoresPanel* f);
        /**
         * Destructor.
         */
        virtual ~GraficoDeTorta();

        void actualizarDatos(const std::list< Hecho >& datos);
    private:
        void hallarNormalizacion(const std::list< Hecho >& datos);
        void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx);
        void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx);
};

#endif  // GRAFICO_DE_TORTA_H
