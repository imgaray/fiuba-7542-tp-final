#ifndef GRAFICO_DE_BARRAS_H
#define GRAFICO_DE_BARRAS_H

#include <gtkmm/drawingarea.h>
#include <list>

#define MAX_VALORES 9

class GraficoDeBarras : public Gtk::DrawingArea {
    public:
        GraficoDeBarras();
        virtual ~GraficoDeBarras();
    protected:
        bool on_expose_event(GdkEventExpose* ev);
    private:
        std::list<double> valores;
        static double colores[MAX_VALORES][3];
        double max;
};

#endif  // GRAFICO_DE_BARRAS_H
