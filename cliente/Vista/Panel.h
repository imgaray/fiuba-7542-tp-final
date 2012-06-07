#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>

class Grafico;
class Filtrador;

class Panel : public Gtk::VBox {
    public:
        Panel(Grafico& g, Filtrador& f);
        ~Panel();
    private:
        Grafico& grafico;
        Filtrador& filtrador;
};

#endif  // PANEL_H__

