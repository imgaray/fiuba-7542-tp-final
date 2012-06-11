#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class Filtrador;
class Consulta;

class FiltradoresTab : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** @todo agregar agregaciones */
        FiltradoresTab();
        ~FiltradoresTab();

        Consulta& filtrar(Consulta& c);

        void agregarEntrada(const std::string& entrada);

    private:
        std::list< Filtrador* > filtradores;
};

#endif  // FILTRADORES_TAB_H
