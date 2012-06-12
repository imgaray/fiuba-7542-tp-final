#include "GraficoDeBarras.h"
#include "Barra.h"
#include <iostream>

#define INIT_OFFSET     0.1
#define SEPARACION_BASE 0.20
#define ANCHO_BASE      0.50
#define MIN_SIZE        4

GraficoDeBarras::GraficoDeBarras(FiltradoresPanel& _f) : Grafico(_f) {
    offset = INIT_OFFSET;
    separacion = SEPARACION_BASE/MIN_SIZE;
    ancho = ANCHO_BASE/MIN_SIZE;
    Hecho juan("Galaxy SII", 10.13);
    Hecho carlos("iPad", 7.5);
    areas.push_back(new Barra(juan, 10.13, 0, separacion, ancho));
    areas.push_back(new Barra(carlos, 10.13, 1, separacion, ancho));
    regenerarReferencias();
}

GraficoDeBarras::~GraficoDeBarras() {}

void GraficoDeBarras::actualizarDatos(const std::list< Hecho >& datos) {
    deleteAreas();
    areas.clear();
    hallarNormalizacion(datos);

    unsigned datosSize = datos.size();
    if (datosSize > MIN_SIZE) {
        separacion = SEPARACION_BASE/datosSize;
        ancho = ANCHO_BASE/datosSize;
    }

    std::list< Hecho >::const_iterator itDatos = datos.begin();
    unsigned i = 0;
    for ( ; itDatos != datos.end(); ++itDatos, ++i)
        areas.push_back(new Barra(*itDatos, normalizacion, i, separacion, ancho));

    regenerarReferencias();
}

void GraficoDeBarras::hallarNormalizacion(const std::list< Hecho >& datos) {
    std::list< Hecho >::const_iterator itDatos = datos.begin();
    normalizacion = -DBL_MAX;
    double siguiente = itDatos->getValor();
    for ( ; itDatos != datos.end(); ++itDatos) {
        if (siguiente > normalizacion)
            normalizacion = siguiente;
        siguiente = itDatos->getValor();
    }
}

void GraficoDeBarras::dibujarEspecializacion(GdkEventExpose* ev,
                                    Cairo::RefPtr< Cairo::Context >& ctx) {
    offset = getOffset();
}

void GraficoDeBarras::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(SEPARACION_BASE+ANCHO_BASE+0.05, 0.1);
}

double GraficoDeBarras::getOffset() {
    return INIT_OFFSET;
}
