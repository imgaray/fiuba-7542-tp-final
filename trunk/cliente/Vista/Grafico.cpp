#include "Grafico.h"
#include <iostream>
#include "Area.h"
#include "FiltradoresPanel.h"
#include "Respuesta.h"

#define MIN_LADO 200

Grafico::Grafico(FiltradoresPanel& _f) : f(_f) {
    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
    set_size_request(MIN_LADO, MIN_LADO);
    setSpinner(&s);
}

Grafico::~Grafico() {
    deleteAreas();
}

void Grafico::hacerConsulta(ServidorRemoto& server) {
    f.filtrar(consulta);
    Consultante::hacerConsulta(server);
}

FiltradoresPanel& Grafico::getFiltrador() const {
    return f;
}

void Grafico::deleteAreas() {
    std::list< Area* >::iterator it;
    for (it = areas.begin(); it != areas.end(); ++it)
        delete *it;
}

void Grafico::regenerarReferencias() {
    std::list< Area* >::const_iterator itAreas = areas.begin();
    referencias.clear();
    for ( ; itAreas != areas.end(); ++itAreas) {
        Referencia refNueva(**itAreas);
        referencias.push_back(refNueva);
    }
    areaSeleccionada = areas.end();
}

bool Grafico::on_expose_event(GdkEventExpose* ev) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Gtk::Allocation allocation = get_allocation();
        ancho_ventana = allocation.get_width();
        alto_ventana = allocation.get_height();
        Cairo::RefPtr<Cairo::Context> ctx = window->create_cairo_context();
        ctx->set_source_rgba(1.0, 1.0, 1.0, 1.0);
        min_lado = ancho_ventana < alto_ventana? ancho_ventana : alto_ventana;
        ctx->rectangle(ev->area.x, ev->area.y, ev->area.width, ev->area.height);
        ctx->fill_preserve();
        ctx->clip();
        ctx->scale(min_lado, min_lado);
        ctx->set_line_width(DEFAULT_LINE_WIDTH);
        ctx->set_source_rgb(0.0, 0.0, 0.0);
        dibujarEspecializacion(ev, ctx);
        dibujarAreas(ctx);
        dibujarReferencias(ctx);
    }

    return true;
}

bool Grafico::on_motion_notify_event(GdkEventMotion* ev) {
//    if (areaSeleccionada != areas.end()); {
//        (*areaSeleccionada)->setSeleccionada(false);
//        areaSeleccionada = areas.end();
//    }
    std::list< Area* >::iterator it = areas.begin();
    bool encontrado = false;
    double offset = getOffset();
    unsigned i = 0;
    while ( !encontrado && it != areas.end()) {
        encontrado = (*it)->fueClickeada(ev->x/min_lado,
                                         ev->y/min_lado, offset);
        (*(it++))->setSeleccionada(false);
        ++i;
    }

    if (encontrado) {
        areaSeleccionada = --it;
        (*areaSeleccionada)->setSeleccionada(true);
        ++it;
        for ( ; it != areas.end(); ++it)
            (*it)->setSeleccionada(false);
        --i;
    }
    else
        areaSeleccionada = areas.end();

    std::list< Referencia >::iterator itRefs = referencias.begin();
    unsigned j = 0;
    for ( ; j < i; ++j, ++itRefs)
        itRefs->setNegrita(false);
    if (itRefs != referencias.end()) {
        itRefs++->setNegrita(true);
        ++j;

        for ( ; j < referencias.size(); ++j, ++itRefs)
            itRefs->setNegrita(false);
    }

    queue_draw_area(0,0, ancho_ventana, alto_ventana);
    return true;
}

bool Grafico::on_button_press_event(GdkEventButton* ev) {
    if (areaSeleccionada == areas.end())
        return true;

    Glib::ustring valor = (*areaSeleccionada)->getEtiqueta();
    padre->difundirNavegacionSeleccionada("Implementando...", valor);
    return true;
}



void Grafico::dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx) {
    std::list< Area* >::iterator it = areas.begin();
    for ( ; it != areas.end(); ++it)
        offset = (*it)->dibujar(ctx, offset);
}

void Grafico::dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx) {
    offset = 0.0;
    std::list< Referencia >::iterator it = referencias.begin();
    for ( ; it != referencias.end(); ++it) {
        dibujarEspecializacionReferencias(ctx);
        offset = it->dibujar(ctx, offset, *this);
    }
}

void Grafico::procesarRespuesta(const Respuesta& rta) {
    if (rta.cantidadColumnas() != 2)
        return;

    double valor;
    std::stringstream ss;
    std::list< Hecho > datos;
    for (unsigned i = 0; i < rta.cantidadFilas(); ++i) {
        ss << rta.dato(i, 1);
        ss >> valor;
        datos.push_back(Hecho(rta.dato(i, 0) , valor));
        ss.clear();
    }

    actualizarDatos(datos);
}

void Grafico::actualizarTamanioMinimo(double x, double y) {

}
