#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "Consultante.h"

class Grafico;
class Filtrador;
class Respuesta;

class Panel : public Gtk::VBox, public Consultante {
    public:
        Panel(Grafico& g, Filtrador& f);
        ~Panel();

        void hacerConsulta();
    private:
        Grafico& grafico;
        Filtrador& filtrador;
        Gtk::ScrolledWindow scrWin;
        Gtk::Viewport* pViewport;

        virtual void procesarRespuesta(const Respuesta& rta);
};

#endif  // PANEL_H__

