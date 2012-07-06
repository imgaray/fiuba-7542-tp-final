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
 * clase encargada de manejar la parte de agregado de filtradores dinámicos
 * por el admin (filtros, inputs, columna X e Y en tabla pivote, y resultados)
 */
class FiltradorConfigManager : public sigc::trackable, public Serializable {
    public:
        FiltradorConfigManager(t_Filt tipo,
                              const filtradoresHandlers& handlers);
        ~FiltradorConfigManager();

        void desconectar();
        void reconectar();

        void setFiltradoresEn(FiltradoresTab* filtTab);
        void setFiltradoresEn(FiltradoresPanel* filtPanel);

        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

// podría haber una señal que indique qué dimensión o hecho fue agregado o eliminado para actualizar todos los restantes combobox

//        sigc::signal< void, ConfigModelo* > signal_model_changed();
    private:
//        sigc::signal< void, ConfigModelo* > _signal_model_changed;
        t_Filt tipo;
        Gtk::VBox* pVBoxFiltradores;
        Gtk::ToolButton* pButtonAgregar;
        FiltradorConfigModelo* new_filtrador();

        /** conexiones a las señales */
        sigc::connection connectionButtonAgregar;

        void on_agregar_button_clicked();
        void on_delete_filtrador(unsigned ID);

        typedef std::pair< FiltradorConfigVista*, FiltradorConfigModelo* > filtrador;
        std::list< filtrador > filtradores;
        FiltradorConfigModelo* ulitmoFilConfigModelo;
        // para una búsqueda más rápida
        std::map< unsigned,  filtrador > mapaFiltradores;
        bool guardandoCambios;
        static unsigned generadorID;
};

#endif  // FILTRADOR_CONFIG_MANAGER_H

