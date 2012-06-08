#ifndef FILTRADOR_H
#define FILTRADOR_H

#include <gtkmm/box.h>
#include "Definiciones.h"
#include "Consultante.h"

class Filtrador : public Gtk::VBox, public Consultante{
    public:
        /** @todo agregar agregaciones */
        Filtrador(const Filtros& filt, const Entradas& entr);
        Filtrador(const Filtrador& filt, const Entradas& entrPanel);
        ~Filtrador();
    private:
        Filtros filtros;
        Entradas entradasTab;
        Entradas entradasPanel;
        std::list< Gtk::Widget* > widgets;
        void procesarRespuesta(const Respuesta& rta);
};

#endif  // FILTRADOR_H
