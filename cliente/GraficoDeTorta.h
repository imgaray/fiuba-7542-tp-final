#ifndef GRAFICO_DE_TORTA_H
#define GRAFICO_DE_TORTA_H

#include <gtkmm/drawingarea.h>
#include <list>

#define MAX_VALORES 9

class GraficoDeTorta : public Gtk::DrawingArea {
    public:
        GraficoDeTorta();
        virtual ~GraficoDeTorta();

        /** Los valores deben sumar 1.
         *  SÓLO por los colores, _valores.size() < MAX_VALORES
         */
        void setValores(const std::list<double>& _valores);

        /** @brief para poder relacionar un valor con una etiqueta par
         * para pegarla en esa porción del gráfico
        void setValores(const std::map<Glib::ustring, double>& valores); // así los reordena
        void setValores(const std::list<std::pair<Glib::ustring, double> >& valores); // así no
        */
    protected:
        virtual bool on_expose_event(GdkEventExpose* ev);
    private:
        std::list<double> valores;
        static double colores[MAX_VALORES][3];
};

#endif  // GRAFICO_DE_TORTA_H
