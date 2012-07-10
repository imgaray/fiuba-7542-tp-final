#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "Definiciones.h"

class Consulta;

/** @class Filtrador
 * Clase abstracta que representa tanto un constructor de consulta como la
 * vista del mismo. Un constructor de consulta es, como se ve en las clases
 * que heredan de esta, un filtro, un input, un resultado y un elemento de
 * X e Y para la tabla pivot.
 */
class Filtrador : public Gtk::HBox {
    public:
        /**
         * Constructor.
         */
        Filtrador(const Glib::ustring& filtro);
        /**
         * Destructor.
         */
        virtual ~Filtrador();

        Glib::ustring getFiltro();

        virtual void filtrar(Consulta& c) = 0;

    protected:
        Gtk::HBox centradorDerecho;

    private:
        Gtk::HBox centradorIzquierdo;
        Gtk::Label filtro;
};

#endif  // FILTRADOR_H
