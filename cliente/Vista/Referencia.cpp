#include "Referencia.h"
#include "Area.h"
#include <iostream>

double Referencia::anchoCuadradito = 0.06;

Referencia::Referencia(const Area& referente) {
    etiqueta = referente.getEtiqueta();
    const double* refColor = referente.getColor();
    for (unsigned i = 0; i < 4; ++i)
        color[i] = refColor[i];
    negrita = false;
}

Referencia::~Referencia() {}

void Referencia::setNegrita(bool estado) {
    negrita = estado;
}

double Referencia::dibujar(Cairo::RefPtr< Cairo::Context >& ctx,
                           double offset) {
    ctx->save();
        double x, y;
        ctx->set_source_rgba(color[0], color[1], color[2], color[3]);
        ctx->get_current_point(x, y);
        ctx->rectangle(x, y+offset, anchoCuadradito, -anchoCuadradito);
        ctx->fill();
        ctx->set_source_rgba(0.0, 0.0, 0.0, 1.0);
        ctx->move_to(x + 1.5*anchoCuadradito, y+offset);
        ctx->set_font_size(anchoCuadradito);
        if (negrita)
            ctx->select_font_face("sans-serif", Cairo::FONT_SLANT_NORMAL,
                                  Cairo::FONT_WEIGHT_BOLD);
        else
            ctx->select_font_face("sans-serif", Cairo::FONT_SLANT_NORMAL,
                                  Cairo::FONT_WEIGHT_NORMAL);
        ctx->show_text(etiqueta);
    ctx->restore();
    return offset + 1.5*anchoCuadradito;
}
