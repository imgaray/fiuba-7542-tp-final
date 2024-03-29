#ifndef FILTRADORES_PANEL_H
#define FILTRADORES_PANEL_H

#include "Filtradores.h"

class FiltradoresTab;

/** @class FiltradoresPanel
 * Implementación concreta de un conjunto de filtradores, el de los paneles.
 * Admiten todos los filtradores existentes, aunque cuando se agrega uno para
 * X o Y de tabla pivote, la consulta al ser filtrada quedará definida como
 * dicha tabla.
 */
class FiltradoresPanel : public Filtradores {
    public:
        /**
         * Constructor.
         * @param filtTab referencia a los filtradores de la tab
         */
        FiltradoresPanel(FiltradoresTab& filtTab);
        /**
         * Destructor.
         */
        ~FiltradoresPanel();

        bool puedeFiltrar();
        void filtrar(Consulta& c);

        /// este método no verifica que el filtro sea dimensión
        void agregarFiltro(const std::string& dimension,
                           const std::string& valor);

        void agregarFiltro(const std::string& filtro,
                           const std::string& valorCombo,
                           const std::string& valorEntrada);

        void agregarEntrada(const std::string& entrada);

        void agregarXTablaP(const std::string& valor);
        void agregarYTablaP(const std::string& valor);

        /// estos tres métodos no verifican que el primer parámetro sea
        /// dimensión, fecha o hecho
        void agregarResultado(const std::string& dimension);
        void agregarResultado(const std::string& fecha,
                              const std::string& valorCombo,
                              const std::string& valorEntrada);
        void agregarResultado(const std::string& hecho,
                              const std::string& agregacion);


        sigc::signal< void > signal_navegabilidad();

    private:
        FiltradoresTab& filtrosHeredados;
        sigc::signal< void > signal_navegabilidad_seleccionada;

        /**
         * Signal handler para FiltradorInput::signal_navegabilidad.
         *
         * Emite FiltradoresPanel::signal_navegabilidad_seleccionada.
         */
        void on_signal_navegabilidad();

        bool esParaTablaPivote;
};

#endif  // FILTRADORES_PANEL_H
