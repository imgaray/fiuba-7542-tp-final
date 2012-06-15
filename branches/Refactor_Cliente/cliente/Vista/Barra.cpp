#include "Barra.h"

#define SEP_TECHO 0.1

Barra::Barra(const Hecho& dato, double maximo, unsigned i,
             double separacion, double _ancho) : Area(dato, maximo, i) {
    sep = separacion;
    ancho = _ancho;
    hasta = dato.getValor() / max - SEP_TECHO;
    y0 = 1.0;
    x0 = 0.0;
}

Barra::~Barra() {}

double Barra::dibujar(Cairo::RefPtr< Cairo::Context >& ctx, double offset) {
    x0 = offset;
    ctx->save();
        if (seleccionada)
            ctx->set_line_width(SELEC_LINE_WIDTH);
        else
            ctx->set_line_width(DEFAULT_LINE_WIDTH);

        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->rectangle(x0, y0, ancho, -hasta);
        ctx->fill_preserve();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->stroke();
    ctx->restore();
    return x0 + ancho + sep;
}

bool Barra::fueClickeada(double x, double y, double& offset) {
    x0 = offset;
    offset += ancho + sep;
    if (x0 < x && x < x0 + ancho &&
        y0 - hasta < y && y < y0)
        return true;
    else
        return false;
}
