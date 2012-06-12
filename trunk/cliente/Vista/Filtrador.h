#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>

class Consulta;

class Filtrador : public Gtk::HBox {
    public:
        Filtrador(const Glib::ustring& filtro);
        virtual ~Filtrador();

        Glib::ustring getFiltro();

        virtual Consulta& filtrar(Consulta& c) = 0;

    protected:
        Gtk::HBox centradorDerecho;

    private:
        Gtk::HBox centradorIzquierdo;
        Gtk::Label filtro;
};

#endif  // FILTRADOR_H
