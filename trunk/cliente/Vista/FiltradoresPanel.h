#ifndef FILTRADORES_PANEL_H
#define FILTRADORES_PANEL_H

#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class FiltradoresTab;
class Filtrador;
class Consulta;

class FiltradoresPanel : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** @todo agregar agregaciones */
        FiltradoresPanel(FiltradoresTab& filtTab);
        ~FiltradoresPanel();

        Consulta& filtrar(Consulta& c);

        /** Si valor es el valor de alguna de las dimensiones
         * o hechos que este conjunto de filtradores filtra,
         * retorna el nombre de la dimensión o hecho
         */
        Glib::ustring pertenece(const Glib::ustring& valor);

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
    private:
        FiltradoresTab& filtrosHeredados;
        std::list< Filtrador* > filtradores;
};

#endif  // FILTRADORES_PANEL_H
