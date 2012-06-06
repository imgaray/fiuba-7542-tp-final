#include "GraficoDeTorta.h"
#include <cairomm/context.h>
#include "PorcionCircular.h"

#define X_0     0.4
#define Y_0     0.5
#define RADIO   0.3

GraficoDeTorta::GraficoDeTorta() {
    offset = 0.0;
}

GraficoDeTorta::~GraficoDeTorta() {}

void GraficoDeTorta::actualizarDatos(const std::list< Hecho >& datos) {
    deleteAreas();
    areas.clear();
    hallarNormalizacion(datos);

    std::list< Hecho >::const_iterator itDatos = datos.begin();
    unsigned i = 0;
    for ( ; itDatos != datos.end(); ++itDatos, ++i)
        areas.push_back(new PorcionCircular(*itDatos, normalizacion, i, X_0, Y_0, RADIO));

    regenerarReferencias();
}

void GraficoDeTorta::hallarNormalizacion(const std::list< Hecho >& datos) {
    normalizacion = 0;
    std::list< Hecho >::const_iterator itDatos = datos.begin();
    for ( ; itDatos != datos.end(); ++itDatos)
        normalizacion += itDatos->getValor();
}

void GraficoDeTorta::dibujarEspecializacion(GdkEventExpose* ev,
                                    Cairo::RefPtr< Cairo::Context >& ctx) {
    offset = getOffset();
}

void GraficoDeTorta::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(0.75, 0.1);
}

double GraficoDeTorta::getOffset() {
    return 0.0;
}
