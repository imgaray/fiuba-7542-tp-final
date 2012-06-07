#ifndef GRAFICO_H
#define GRAFICO_H

#include <list>
#include <gtkmm/drawingarea.h>
#include "Referencia.h"
#include "Hecho.h"

class Area;

class Grafico : public Gtk::DrawingArea {
    public:
        Grafico();
        virtual ~Grafico();

        virtual void actualizarDatos(const std::list< Hecho >& datos) = 0;
    protected:
        std::list< Area* > areas;
        double offset;
        double normalizacion;

        virtual void hallarNormalizacion(const std::list< Hecho >& datos) = 0;
        /** borra y regenera todas las referencias */
        void deleteAreas();
        void regenerarReferencias();
        virtual bool on_expose_event(GdkEventExpose* ev);
        virtual void dibujarEspecializacion(GdkEventExpose* ev,
                            Cairo::RefPtr< Cairo::Context >& ctx) = 0;
        virtual void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx) = 0;
        virtual double getOffset() = 0;
        /** itera por las áreas y las grafica donde esté puesto el contexto */
        virtual void dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx);
        /** itera por las referencias y las grafica donde esté puesto el contexto */
        virtual void dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx);
    private:
        std::list< Referencia > referencias;
        bool on_button_press_event(GdkEventButton* ev);
        int ancho_ventana;
        int alto_ventana;
        int min_lado;
};
#endif  // GRAFICO_H