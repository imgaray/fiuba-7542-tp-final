#ifndef FILTRADORES_PANEL_H
#define FILTRADORES_PANEL_H

#include <gtkmm/box.h>

class Filtrador;

class FiltradoresPanel : public Gtk::VBox {
    public:
        FiltradoresPanel();
        ~FiltradoresPanel();

        /// este método no verifica que el filtro sea dimensión
        void agregarFiltro(const std::string& dimension,
                           const std::string& valor);

        void agregarFiltro(const std::string& filtro,
                           const std::string& valorCombo,
                           const std::string& valorEntrada);

        void agregarEntrada(const std::string& entrada);

        void agregarResultado(const std::string& dimension);
        void agregarResultado(const std::string& fecha,
                              const std::string& valorCombo,
                              const std::string& valorEntrada);
        void agregarResultado(const std::string& hecho,
                              const std::string& agregacion);
    private:
        std::list< Filtrador* > filtradores;
};

#endif  // FILTRADORES_PANEL_H
