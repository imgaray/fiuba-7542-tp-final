#ifndef GRAFICO_H
#define GRAFICO_H

#include <list>
#include <gtkmm/drawingarea.h>
#include <gtkmm/layout.h>
#include <gtkmm/viewport.h>
#include "Referencia.h"
#include "Hecho.h"
#include "Consultante.h"
#include "Filtrador.h"

class Area;
class FiltradoresPanel;

class Grafico : public Gtk::DrawingArea, public Consultante {
    public:
        Grafico(FiltradoresPanel& f);
        virtual ~Grafico();

        virtual void hacerConsulta(ServidorRemoto& server);

        /** @todo implementar para cuando las referencias no entran en el [0,1]x[0,1] */
        void actualizarTamanioMinimo(double x, double y);
        FiltradoresPanel& getFiltrador() const;
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
        std::list< Area* >::iterator areaSeleccionada;
        bool on_button_press_event(GdkEventButton* ev);
        bool on_motion_notify_event(GdkEventMotion* ev);
        int ancho_ventana;
        int alto_ventana;
        int min_lado;
        FiltradoresPanel& f;
        void procesarRespuesta(const Respuesta& rta);
        virtual void actualizarDatos(const std::list< Hecho >& datos) = 0;
        Gtk::Spinner s;
};
#endif  // GRAFICO_H
