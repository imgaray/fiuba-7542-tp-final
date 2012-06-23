#ifndef FILTRADORES_PANEL_H
#define FILTRADORES_PANEL_H

#include <list>
#include <queue>
#include <gtkmm/box.h>

class FiltradoresTab;
class Filtrador;
class FiltradorInput;
class FiltradorInputDimension;
class Consulta;

class FiltradoresPanel : public Gtk::VBox {
    public:
        /** @todo agregar agregaciones */
        FiltradoresPanel(FiltradoresTab& filtTab);
        ~FiltradoresPanel();

        void filtrar(Consulta& c);

        /// este método no verifica que el filtro sea dimensión
        void agregarFiltro(const std::string& dimension,
                           const std::string& valor);

        void agregarFiltro(const std::string& filtro,
                           const std::string& valorCombo,
                           const std::string& valorEntrada);

        void agregarEntrada(const std::string& entrada);

        /// estos tres métodos no verifican que el primer parámetro sea
        /// dimensión, fecha o hecho
        void agregarResultado(const std::string& dimension);
        void agregarResultado(const std::string& fecha,
                              const std::string& valorCombo,
                              const std::string& valorEntrada);
        void agregarResultado(const std::string& hecho,
                              const std::string& agregacion);

        bool tieneFiltrosNavegables();
        bool tieneFiltrosConsultantes();

        FiltradorInput* getFiltroNavegable();
        FiltradorInputDimension* getFiltroConsultante();

        sigc::signal< void > signal_navegabilidad();

    private:
        FiltradoresTab& filtrosHeredados;
        std::list< Filtrador* > filtradores;
        std::queue< FiltradorInput* > filtrosNavegables;
        std::queue< FiltradorInputDimension* > filtrosConsultantes;
        sigc::signal< void > signal_navegabilidad_seleccionada;
        void on_signal_navegabilidad();
};

#endif  // FILTRADORES_PANEL_H
