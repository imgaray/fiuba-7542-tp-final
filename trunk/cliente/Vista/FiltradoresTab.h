#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class FiltradoresTab : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** @todo agregar agregaciones */
        FiltradoresTab();
        ~FiltradoresTab();

        void agregarEntrada(const std::string& entrada);
    private:
        std::list< Gtk::Widget* > widgets;
};

#endif  // FILTRADORES_TAB_H
