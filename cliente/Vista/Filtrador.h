#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>

#define FILTRO      'F'
#define RESULTADO   'R'

class Validador;

typedef std::list< Glib::ustring > Campos;

class Filtrador : public Gtk::HBox {
    public:
        Filtrador(char tipo, const Glib::ustring& nombre);
        Filtrador(char tipo, const Glib::ustring& etiqueta, const Glib::ustring& nombre);
    protected:
        Gtk::HBox centradorDerecho;
        Validador* valid;
        Gtk::Label etiqueta;
        Glib::ustring nombre;
    private:
        Gtk::HBox centradorIzquierdo;
        char tipo;
};
#endif  // FILTRADOR_H
