#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include <list>
#include <queue>
#include <gtkmm/box.h>

class Filtrador;
class FiltradorInput;
class FiltradorInputDimension;
class Consulta;

class FiltradoresTab : public Gtk::VBox {
    public:
        /** @todo agregar agregaciones */
        FiltradoresTab();
        ~FiltradoresTab();

        void filtrar(Consulta& c);

        void agregarEntrada(const std::string& entrada);

        bool tieneFiltrosNavegables();
        bool tieneFiltrosConsultantes();

        FiltradorInput* getFiltroNavegable();
        FiltradorInputDimension* getFiltroConsultante();

    private:
        std::list< Filtrador* > filtradores;
        std::queue< FiltradorInput* > filtrosNavegables;
        std::queue< FiltradorInputDimension* > filtrosConsultantes;
};

#endif  // FILTRADORES_TAB_H
