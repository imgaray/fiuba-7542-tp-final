#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"
#include "Definiciones.h"
#include "Consultante.h"

class Filtrador : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** @todo agregar agregaciones */
        Filtrador(const Filtros& filt, const Entradas& entr);
        Filtrador(const Filtrador& filt, const Entradas& entrPanel);
        ~Filtrador();

        void hacerConsulta();
    private:
        Filtros filtros;
        Entradas entradasTab;
        Entradas entradasPanel;
        std::list< Gtk::Widget* > widgets;
};

#endif  // FILTRADOR_H
