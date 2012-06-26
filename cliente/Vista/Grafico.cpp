#include "Grafico.h"
#include <iostream>
#include <exception>
#include "Area.h"
#include "FiltradoresPanel.h"
#include "Respuesta.h"
#include "Tab.h"

#define MIN_LADO 200
#define COL_RESULTADO 0  // constante que hace que siempre se tome la columna 0 de la respuesta para dar nombre a las áreas del gráfico
#define SIN_DATOS "No hay resultados para mostrar"

Grafico::Grafico(FiltradoresPanel& _f) : f(_f) {
    f.signal_navegabilidad().connect(sigc::mem_fun(*this,
        &Consultante::on_navegabilidad_seleccionada));
    add_events(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK);
    set_size_request(MIN_LADO, MIN_LADO);
    setSpinner(&s);
    furthest_p = 0;
    min_lado = 0;
}

Grafico::~Grafico() {
    deleteAreas();
}

void Grafico::hacerConsulta(ServidorRemoto& server) {
    consulta.limpiar();
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
//        int min_lado_nuevo = ancho_ventana < alto_ventana? ancho_ventana : alto_ventana;
//        min_lado = min_lado > min_lado_nuevo? min_lado : min_lado_nuevo;
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
        resize();
    }

    return true;
}

bool Grafico::on_motion_notify_event(GdkEventMotion* ev) {
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
    if (ev->button != 1)
        return true;
    if (areaSeleccionada == areas.end())
        return true;

    Glib::ustring valor = (*areaSeleccionada)->getEtiqueta();
    Glib::ustring input = consulta.resultado(COL_RESULTADO);
    if (input == STR_NULA)
        std::cout << "Hiciste algo mal" << std::endl;

    padre->difundirNavegacionSeleccionada(input, valor);
    return true;
}

void Grafico::dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx) {
    if (areas.empty()) {
        ctx->save();
            ctx->move_to(0.14, 0.5);
            ctx->set_font_size(0.08);
            ctx->show_text(SIN_DATOS);
        ctx->restore();
    } else {
        std::list< Area* >::iterator it = areas.begin();
        for ( ; it != areas.end(); ++it)
            offset = (*it)->dibujar(ctx, offset);
    }
}

void Grafico::dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx) {
    offset = 0.0;
    std::list< Referencia >::iterator it = referencias.begin();
    for ( ; it != referencias.end(); ++it) {
        dibujarEspecializacionReferencias(ctx);
        offset = it->dibujar(ctx, offset, *this);
    }
}

/** @todo remover */
using std::string; using std::cout; using std::endl;
void imprimirRespuesta(const Respuesta& resp, const string& comentario) {
	cout << endl;
	cout << "Comentario: " << comentario << endl;
	cout << "Estado Resp: " << resp.mensajeInterno() << endl;
	cout << "Cantidad Filas: " << resp.cantidadFilas() << endl;
	cout << "Cantidad Columnas: " << resp.cantidadColumnas() << endl;
	cout << "Datos Recibidos:" << endl;
	for (unsigned i = 0; i < resp.cantidadFilas() ; i++)  {
		cout << "::";
		for (unsigned j = 0 ; j < resp.cantidadColumnas() ; j++) {
			cout.width(14);
			cout.fill('.');
			cout<< resp.dato(i,j) << "|";
		}
		cout << endl;
	}
}

void Grafico::procesarRespuesta(const Respuesta& rta) {
    std::cout << "cantidad de columnas " << rta.cantidadColumnas() << std::endl;
    if (rta.cantidadColumnas() != 2)
        throw "Respuesta para grafico con más o menos de dos columnas";

    imprimirRespuesta(rta, "Tu hermana");

    double valor;
    std::stringstream ss;
    std::list< Hecho > datos;
    for (unsigned i = 0; i < rta.cantidadFilas(); ++i) {
        ss << rta.dato(i, 1);
        ss >> valor;
        datos.push_back(Hecho(rta.dato(i, COL_RESULTADO) , valor));
        ss.clear();
    }

    actualizarDatos(datos);
    queue_draw_area( 0, 0, ancho_ventana, alto_ventana);
}

void Grafico::actualizarTamanioMinimo(double x, double y) {
//    std::cout << "\n\n\nvoid Grafico:actualizarTamanioMinimo(double, double )" << std::endl
//              << "Hay datos hasta: ( x, y ) == ( " << x << ", " << y << " )\n\n\n" << std::endl;
//    int min_x, min_y;
//    if (x > 1)
//        min_x = MIN_LADO*x;
//    if (y > 1)
//        min_y = MIN_LADO*y;
//    if (x > 1 && y > 1)
//        set_size_request(min_x, min_y);
    furthest_p = x > furthest_p? x : furthest_p;
    furthest_p = y > furthest_p? y : furthest_p;
}

void Grafico::resize() {
    if (furthest_p > 1) {
//        min_lado *= furthest_p;
//        ctx->scale(min_lado, min_lado);
//    queue_draw_area( 0, 0, ancho_ventana, alto_ventana);
        int temp = MIN_LADO * furthest_p;
        set_size_request(temp, temp);
//        std::cout << "MIN_LADO nuevo: " << temp << std::endl;
        furthest_p = 1;
    }
}
