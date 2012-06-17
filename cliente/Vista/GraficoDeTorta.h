#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

#ifndef MAX_VALORES
#define MAX_VALORES 9
#endif

class GraficoDeTorta : public Grafico {
    public:
        GraficoDeTorta();
        virtual ~GraficoDeTorta();

    private:
        void hallarNormalizacion(const std::list< Hecho >& datos);
        void dibujarEspecializacion(GdkEventExpose* ev,
                                    Cairo::RefPtr< Cairo::Context >& ctx);
        void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx);
        double getOffset();

        void actualizarDatos(const std::list< Hecho >& datos);
};

#endif  // GRAFICO_DE_TORTA_H
