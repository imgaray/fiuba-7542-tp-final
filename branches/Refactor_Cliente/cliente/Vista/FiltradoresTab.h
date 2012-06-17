#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class Filtrador;

class FiltradoresTab : public Gtk::VBox {
    public:
        FiltradoresTab();
        ~FiltradoresTab();

        void agregarEntrada(const std::string& entrada);

    private:
        std::list< Filtrador* > filtradores;
};

#endif  // FILTRADORES_TAB_H
