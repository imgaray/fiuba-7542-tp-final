#include "Barra.h"

#define SEP_TECHO 0.1

Barra::Barra(const Hecho& dato, double maximo, unsigned i,
             double separacion, double _ancho) : Area(dato, maximo, i) {
    sep = separacion;
    ancho = _ancho;
}

Barra::~Barra() {}

double Barra::dibujar(Cairo::RefPtr< Cairo::Context >& ctx, double offset) {
    double hasta = dato.getValor() / max - SEP_TECHO;
    ctx->save();
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->rectangle(offset, 1.0, ancho, -hasta);
        ctx->fill_preserve();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->stroke();
    ctx->restore();
    return offset + ancho + sep;
}

bool Barra::fueClickeada(double x, double y, double& offset) {
    return false;
}
