#include "GraficoDeBarras.h"

// colores asquerosamente hardcodeados
double GraficoDeBarras::colores[MAX_VALORES][3] = {
    {0.77, 0.2, 0.4}, {0.4, 0.77, 0.2}, {0.4, 0.3, 0.77},
    {0.7, 0.3, 0.77}, {0.1, 0.7, 0.77}, {0.4, 0.3, 0.77},
    {0.4, 0.67, 0.9}, {0.9, 0.67, 0.4}, {0.9, 0.4, 0.67}
};
GraficoDeBarras::GraficoDeBarras() {
    valores.push_back(13.4);
    valores.push_back(20.5);
    valores.push_back(10.39);
    valores.push_back(5.7);
    max = 20.5;
}

GraficoDeBarras::~GraficoDeBarras() {}

bool GraficoDeBarras::on_expose_event(GdkEventExpose* ev) {
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
        ctx->set_source_rgb(0.0, 0.0, 0.0);
        const float separacion = 0.3/valores.size();
        const float ancho = 0.7/valores.size();
        float pos = 0;
        std::list<double>::const_iterator it;
        unsigned i = 0;

        for (it = valores.begin(); it != valores.end(); ++it, ++i) {
            ctx->save();
            ctx->set_source_rgb(colores[i][0], colores[i][1], colores[i][2]);
            ctx->rectangle(pos, 1.0, ancho, -*it/max);
            pos += ancho + separacion;
            ctx->fill_preserve();
            ctx->restore();
            ctx->stroke();
        }
    }
    return true;
}
