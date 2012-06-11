#ifndef FILTRADORES_PANEL_H
#define FILTRADORES_PANEL_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class FiltradoresTab;
class Filtrador;

class FiltradoresPanel : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** @todo agregar agregaciones */
        FiltradoresPanel(FiltradoresTab& filtTab);
        ~FiltradoresPanel();

        Consulta& filtrar(Consulta& c);

        void agregarFiltro(const std::string& filtro,
                           const std::string& valor);
        void agregarEntrada(const std::string& entrada);

        /// estos tres métodos no verifican que el primer parámetro sea
        /// dimensión, fecha o hecho
        void agregarResultado(const std::string& dimension);
        void agregarResultado(const std::string& fecha,
                              const std::string& valorCombo,
                              const std::string& valorEntrada);
        void agregarResultado(const std::string& hecho,
                              const std::string& agregacion);
    private:
        FiltradoresTab& filtrosHeredados;
        std::list< Filtrador* > filtradores;
};

#endif  // FILTRADORES_PANEL_H
