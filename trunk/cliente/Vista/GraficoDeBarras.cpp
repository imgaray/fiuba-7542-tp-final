#include "GraficoDeBarras.h"
#include "Barra.h"
#include <iostream>

#define INIT_OFFSET     0.1
#define SEPARACION_BASE 0.20
#define ANCHO_BASE      0.50
#define MIN_SIZE        4

GraficoDeBarras::GraficoDeBarras(FiltradoresPanel& _f) : Grafico(_f) {
    separacion = SEPARACION_BASE/MIN_SIZE;
    ancho = ANCHO_BASE/MIN_SIZE;
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
    double offset = INIT_OFFSET;
    for ( ; itDatos != datos.end(); ++itDatos, ++i) {
        Barra* barra = new Barra(*itDatos, normalizacion, i, offset,
                                  separacion, ancho);
        offset = barra->getAvance();
        areas.push_back(barra);
    }

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

void GraficoDeBarras::dibujarEspecializacionReferencias(
        Cairo::RefPtr< Cairo::Context >& ctx) {
    ctx->move_to(SEPARACION_BASE+ANCHO_BASE+0.1, 0.1);
}
