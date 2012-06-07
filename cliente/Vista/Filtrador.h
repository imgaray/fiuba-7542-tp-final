#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include "../../comun/Definiciones.h"

class Filtrador : public Gtk::VBox {
    public:
        /** @todo agregar agregaciones */
        Filtrador(const Filtros& filt, const Entradas& entr);
        ~Filtrador();
    private:
        Filtros filtros;
        Entradas entradas;
        std::list< Gtk::Widget* > widgets;
};

#endif  // FILTRADOR_H
