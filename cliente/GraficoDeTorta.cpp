#include "GraficoDeTorta.h"
#include <cairomm/context.h>
#include <pangomm/context.h>
#include <pangomm/layout.h>
#include <cmath>

// colores asquerosamente hardcodeados
double GraficoDeTorta::colores[MAX_VALORES][3] = {
    {0.77, 0.2, 0.4}, {0.4, 0.77, 0.2}, {0.4, 0.3, 0.77},
    {0.7, 0.3, 0.77}, {0.1, 0.7, 0.77}, {0.4, 0.3, 0.77},
    {0.4, 0.67, 0.9}, {0.9, 0.67, 0.4}, {0.9, 0.4, 0.67}
};

GraficoDeTorta::GraficoDeTorta() {
    valores.push_back(0.39);
    valores.push_back(0.33);
    valores.push_back(0.28);

    /** para ver los colores :P */
//    valores.push_back(0.12);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
//    valores.push_back(0.11);
}

GraficoDeTorta::~GraficoDeTorta() {}

bool GraficoDeTorta::on_expose_event(GdkEventExpose* ev) {
    Glib::RefPtr<Gdk::Window> window = get_window();
    if (window) {
        Gtk::Allocation allocation = get_allocation();
        const int width = allocation.get_width();
        const int height = allocation.get_height();
        Cairo::RefPtr<Cairo::Context> ctx = window->create_cairo_context();
        ctx->rectangle(ev->area.x, ev->area.y, ev->area.width, ev->area.height);
        ctx->clip();
        int min = width < height? width : height;
        ctx->scale(min, min);
        ctx->set_line_width(0.01);
        double angulo = 0.0;
        ctx->set_source_rgb(0.0, 0.0, 0.0);

//        Glib::RefPtr<Pango::Layout> pangoLayout = Pango::Layout::create(ctx);
//        pangoLayout->set_text("Prueba");
        std::list<double>::const_iterator it;
        unsigned i = 0;
        for (it = valores.begin(); it != valores.end(); ++it, ++i) {
            ctx->save();
            ctx->move_to(0.5, 0.5);
            ctx->arc(0.5, 0.5, 0.4, angulo, angulo + 2*M_PI*(*it));
            angulo += 2*M_PI*(*it);
            ctx->close_path();
            ctx->set_source_rgb(colores[i][0], colores[i][1], colores[i][2]);
            ctx->fill_preserve();
            ctx->restore();
            ctx->stroke();
//            pangoLayout->show_in_cairo_context(ctx);
        }
    }

    return true;
}

void GraficoDeTorta::setValores(const std::list<double>& _valores) {
    if (_valores.size() < MAX_VALORES) {
        valores.empty();
        valores.assign(_valores.begin(), _valores.end());
    }
}
