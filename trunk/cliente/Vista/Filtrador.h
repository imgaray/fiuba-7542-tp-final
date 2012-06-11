#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>

class Filtrador : public Gtk::HBox {
    public:
        Filtrador(const Glib::ustring& filtro);
        virtual ~Filtrador();

    protected:
        Gtk::HBox centradorDerecho;
    private:
        Gtk::HBox centradorIzquierdo;
        Gtk::Label filtro;
};

#endif  // FILTRADOR_H
