#ifndef FILTRADORES_H
#define FILTRADORES_H

#include <list>
#include <queue>
#include <gtkmm/box.h>

class Filtrador;
class FiltradorInput;
class FiltradorInputDimension;
class Consulta;

/** @class Filtradores
 * Clase abstracta que representa tanto un conjunto de filtradores como la
 * vista del conjunto. Cada filtrador se dispone uno abajo del otro.
 */
class Filtradores : public Gtk::VBox {
    public:
        Filtradores();
        ~Filtradores();

        virtual bool puedeFiltrar();
        virtual void filtrar(Consulta& c);

        virtual void agregarEntrada(const std::string& entrada) = 0;

        bool tieneFiltrosNavegables();
        bool tieneFiltrosConsultantes();

        FiltradorInput* getFiltroNavegable();
        FiltradorInputDimension* getFiltroConsultante();

    protected:
        std::list< Filtrador* > filtradores;
        std::queue< FiltradorInput* > filtrosNavegables;
        std::queue< FiltradorInputDimension* > filtrosConsultantes;
        unsigned cant_inputs, inputsDisponibles;
        bool _puedeFiltrar;


        /**
         * Signal handler para la señal
         * FiltradorInput::_signal_input_disponible.
         *
         * Aumenta o disminuye la cantidad de inputs disponibles, según sea
         * true o false el parámetro. Si todos los inputs están disponibles
         * entonces puede filtrar una consulta.
         * @param estado estado de la disponibilidad del input
         */
        void on_input_esta_disponible(bool estado);
};

#endif  // FILTRADORES_H
