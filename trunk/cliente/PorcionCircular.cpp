#include "PorcionCircular.h"
#include <cmath>
#include <iostream>

PorcionCircular::PorcionCircular(const Hecho& dato, double maximo, unsigned i,
                                 double _x0, double _y0, double radio)
    : Area(dato, maximo, i) {
    x0 = _x0;
    y0 = _y0;
    r = radio;
}

PorcionCircular::~PorcionCircular() {}

double PorcionCircular::dibujar(Cairo::RefPtr< Cairo::Context >& ctx,
                                double offset) {
    double hasta = offset + 2*M_PI*(dato.getValor()/max);
    ctx->save();
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->move_to(x0, y0);
        ctx->arc(x0, y0, r, offset, hasta);
        ctx->move_to(x0, y0);
        ctx->close_path();
        ctx->fill_preserve();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->stroke();
    ctx->restore();
    return hasta;
}

bool PorcionCircular::fueClickeada(double x, double y, double& offset) {
    return false;
}

