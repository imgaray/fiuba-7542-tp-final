#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>

class Grafico;

class Panel : public Gtk::VBox {
    public:
        Panel(Grafico& g);
        ~Panel();
    private:
        Grafico& grafico;
};

#endif  // PANEL_H__

