#ifndef GRAFICO_DE_BARRAS_H
#define GRAFICO_DE_BARRAS_H

#include "Grafico.h"

/** @class GraficoDeBarras
 * Consultante que muestra sus resultados como un gráfico de barras.
 */
class GraficoDeBarras : public Grafico {
    public:
        GraficoDeBarras(FiltradoresPanel* f);
        virtual ~GraficoDeBarras();

        void actualizarDatos(const std::list< Hecho >& datos);
    private:
        void hallarNormalizacion(const std::list< Hecho >& datos);
        void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx);
        void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx);
        double separacion;
        double ancho;
        double espacio;
        unsigned datosSize;
};

#endif  // GRAFICO_DE_BARRAS_H
