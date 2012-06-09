#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "PadreDeConsultantes.h"

class Grafico;
class Filtrador;

class Panel : public Gtk::VBox, public PadreDeConsultantes {
    public:
        Panel(Grafico& g, Filtrador& f);
        ~Panel();

        void hacerConsulta();
    private:
        Grafico& grafico;
        Filtrador& filtrador;
        Gtk::ScrolledWindow scrWin;
        Gtk::Viewport* pViewport;
};

#endif  // PANEL_H__

