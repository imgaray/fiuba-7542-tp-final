#ifndef PANEL_H__
#define PANEL_H__

#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/frame.h>
#include <gtkmm/viewport.h>

class Grafico;
class Tabla;
class FiltradoresPanel;

class Panel : public Gtk::Frame {
    public:
        Panel(const Glib::ustring& label);
        ~Panel();

        // Agrega también a los filtradores, pidiéndoselos al gráfico
        void setContenido(Grafico& g);
        void setContenido(Tabla& t);
    private:
        Gtk::VBox box;
        Gtk::ScrolledWindow scrWin;
        Gtk::Viewport* pViewport;
};

#endif  // PANEL_H__

