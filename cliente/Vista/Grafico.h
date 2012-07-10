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
        Grafico(FiltradoresPanel* f);
        virtual ~Grafico();

    protected:
        std::list< Area* > areas;
        double normalizacion;

        virtual void hallarNormalizacion(const std::list< Hecho >& datos) = 0;
        /** borra y regenera todas las referencias */
        void deleteAreas();
        void regenerarReferencias();

    private:
        virtual void dibujarEspecializacionReferencias(
                Cairo::RefPtr< Cairo::Context >& ctx) = 0;
        /** itera por las áreas y las grafica donde esté puesto el contexto */
        void dibujarAreas(Cairo::RefPtr< Cairo::Context >& ctx);
        /** itera por las referencias y las grafica donde esté puesto el contexto */
        void dibujarReferencias(Cairo::RefPtr< Cairo::Context >& ctx);

        std::list< Referencia > referencias;
        std::list< Area* >::iterator areaSeleccionada;

        virtual void dibujarEspecializacion(GdkEventExpose* ev,
                        Cairo::RefPtr< Cairo::Context >& ctx) = 0;


        /**
         * @brief Signal handler para el evento Gtk::Widget::signal_expose_event.
         * @return true siempre, el manejo del evento termina acá.
         *
         * Regrafica todo el widget.
         */
        bool on_expose_event(GdkEventExpose* ev);

        /**
         * @brief Signal handler para el evento Gtk::Widget::signal_button_press_event.
         * @return true siempre, el manejo del evento termina acá.
         *
         * Sólo toma el click del botón izquierdo del mouse.
         * Si el área seleccionada es válida, inicializa la cascada de llamadas
         * (void Tab::difundirNavegacionSeleccionada(const Glib::ustring& ,
         * const Glib::ustring& )) para que se interprete la navegación.
         */
        bool on_button_press_event(GdkEventButton* ev);

        /**
         * @brief Signal handler para el evento Gtk::Widget::signal_motion_notify_event.
         * @return true siempre, el manejo del evento termina acá.
         *
         * Itera por las áreas hasta encontrar la seleccionada por el usuario,
         * que es aquella que se encuentra debajo del mouse. Si hubo cambios,
         * agrega un evento de redibujado a la cola de eventos.
         */
        bool on_motion_notify_event(GdkEventMotion* ev);
        int ancho_ventana;
        int alto_ventana;
        int min_lado;
        bool should_request_size;
        double furthest_x, furthest_y;
        void resize();

        /** modelo */
        void procesarRespuesta(const Respuesta& rta);
        virtual void actualizarDatos(const std::list< Hecho >& datos) = 0;
        void actualizarTamanioMinimo(double x, double y);
        Gtk::Spinner s;
};
#endif  // GRAFICO_H
