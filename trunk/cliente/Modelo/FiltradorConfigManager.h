#ifndef FILTRADOR_CONFIG_MANAGER_H
#define FILTRADOR_CONFIG_MANAGER_H

#include "TabConfigModelo.h"
#include "DefinicionesXML.h"

enum t_Filt {
    FILT_FILTRO,
    FILT_INPUT,
    FILT_PIVOTE_X,
    FILT_PIVOTE_Y,
    FILT_RESULTADO
};

class FiltradorConfigModelo;
class FiltradorConfigVista;
class FiltradoresTab;
class FiltradoresPanel;

/** @class FiltradorConfigManager
 * Clase encargada de manejar la parte de agregado de filtradores dinámicos
 * por el admin (filtros, inputs, columna X e Y en tabla pivote, y resultados).
 *
 * Implementa una pequeña factory en base al enum t_Filt.
 *
 * Está conectado a una señal, en cada uno de los objetos que controla, que
 * informa qué campos están disponibles para ser seleccionados. Al recibirla,
 * la difunde por todos sus objetos.
 */
class FiltradorConfigManager : public sigc::trackable, public Serializable {
    public:
        /**
         * Constructor.
         */
        FiltradorConfigManager(t_Filt tipo,
                              const filtradoresHandlers& handlers);
        /**
         * Destructor.
         */
        ~FiltradorConfigManager();

        void desconectar();
        void reconectar();

        void setFiltradoresEn(FiltradoresTab* filtTab);
        void setFiltradoresEn(FiltradoresPanel* filtPanel);

        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    private:
        t_Filt tipo;
        Gtk::VBox* pVBoxFiltradores;
        Gtk::ToolButton* pButtonAgregar;
        FiltradorConfigModelo* new_filtrador();

        /* conexiones a las señales */
        sigc::connection connectionButtonAgregar;


        /**
         * Signal handler para el click sobre el botón agregar filtrador.
         *
         * Agrega un filtrador del tipo adecuado, mientras haya campos no
         * utilizados. Cuando se acaban, deja de ser sensible el botón a los
         * clicks y se informa en un tooltip la razón.
         */
        void on_agregar_button_clicked();

        /**
         * Signal handler para el cambio de selección del campo en el combobox.
         *
         * Agrega a la lista de campos disponibles campoAnterior, y remueve
         * campoNuevo. Itera por todos los filtradores informándoles que tienen
         * que remover de sus opciones campoNuevo, y agregar campoAnterior.
         * @param campoAnterior el campo seleccionado antes
         * @param campoNuevo el campo seleccionado próximamente
         */
        void on_filtrador_campo_changed(Glib::ustring campoAnterior,
                                        Glib::ustring campoNuevo);

        /**
         * Signal handler para el click sobre el botón de eliminar filtrador.
         *
         * Remueve el filtrador de ID del mapa, lista, vista. Libera su
         * memoria, y quita el tooltip del botón de agregar y lo vuelve
         * sensible.
         * @param ID identificador del filtrador
         */
        void on_delete_filtrador(unsigned ID);

        typedef std::pair< FiltradorConfigVista*, FiltradorConfigModelo* > filtrador;
        std::list< filtrador > filtradores;
        std::list< std::string > camposTomados;
        FiltradorConfigModelo* ulitmoFilConfigModelo;
        // para una búsqueda más rápida
        std::map< unsigned,  filtrador > mapaFiltradores;
        bool guardandoCambios;
        static unsigned generadorID;
};

#endif  // FILTRADOR_CONFIG_MANAGER_H

