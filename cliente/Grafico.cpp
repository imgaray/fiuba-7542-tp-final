#include "Grafico.h"
#include <iostream>
#include "Area.h"

Grafico::Grafico() {
    add_events(Gdk::BUTTON_PRESS_MASK);
}

Grafico::~Grafico() {
    deleteAreas();
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
}

bool Grafico::on_expose_event(GdkEventExpose* ev) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Gtk::Allocation allocation = get_allocation();
        ancho_ventana = allocation.get_width();
        alto_ventana = allocation.get_height();
        Cairo::RefPtr<Cairo::Context> ctx = window->create_cairo_context();
        ctx->set_source_rgba(1.0, 1.0, 1.0, 1.0);
        ctx->rectangle(ev->area.x, ev->area.y, ev->area.width, ev->area.height);
        ctx->fill_preserve();
        ctx->clip();
        min_lado = ancho_ventana < alto_ventana? ancho_ventana : alto_ventana;
        ctx->scale(min_lado, min_lado);
        ctx->set_line_width(0.01);
        ctx->set_source_rgb(0.0, 0.0, 0.0);
        dibujarEspecializacion(ev, ctx);
        dibujarAreas(ctx);
        dibujarReferencias(ctx);
    }

    return true;
}

bool Grafico::on_button_press_event(GdkEventButton* ev) {
    std::list< Area* >::const_iterator it = areas.begin();
    bool encontrado = false;
    double offset = getOffset();
    while ( !encontrado && it != areas.end()) {
        encontrado = (*it)->fueClickeada(ev->x/min_lado,
                                         ev->y/min_lado, offset);
        ++it;
    }
    std::cout << "Click en: ( " << ev->x << ", " << ev->y << ") = ( "
              << ev->x/min_lado <<", " << ev->y/min_lado << ")" << std::endl;
    if (encontrado)
        std::cout << (*it)->getEtiqueta() << " clickeado." << std::endl;
    else
        std::cout << "Clickeada la nada misma" << std::endl;

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
        offset = it->dibujar(ctx, offset);
    }
}
