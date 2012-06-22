#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include "Grafico.h"

class GraficoDeTorta : public Grafico {
    public:
        GraficoDeTorta(FiltradoresPanel& f);
        virtual ~GraficoDeTorta();

        void actualizarDatos(const std::list< Hecho >& datos);
    private:
        void hallarNormalizacion(const std::list< Hecho >& datos);
        void dibujarEspecializacion(GdkEventExpose* ev,
                                    Cairo::RefPtr< Cairo::Context >& ctx);
        void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx);
        double getOffset();
};

#endif  // GRAFICO_DE_TORTA_H
