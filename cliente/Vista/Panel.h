#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include "PadreDeConsultantes.h"

class Grafico;
class FiltradoresPanel;

class Panel : public Gtk::VBox, public PadreDeConsultantes {
    public:
        Panel(Grafico& g, FiltradoresPanel& f);
        ~Panel();

        void hacerConsulta();
    private:
        Grafico& grafico;
        FiltradoresPanel& filtrador;
        Gtk::ScrolledWindow scrWin;
        Gtk::Viewport* pViewport;
};

#endif  // PANEL_H__

