#ifndef FILTRADOR_CONFIG_MANAGER_H
#define FILTRADOR_CONFIG_MANAGER_H

#include "TabConfigModelo.h"

enum t_Filt {
    FILT_FILTRO,
    FILT_INPUT,
    FILT_PIVOTE_X,
    FILT_PIVOTE_Y,
    FILT_RESULTADO
};

class FiltradorConfigModelo;
class FiltradorConfigVista;

/** @class FiltradorConfigManager
 * clase encargada de manejar la parte de agregado de filtradores dinámicos
 * por el admin (filtros, inputs, columna X e Y en tabla pivote, y resultados)
 */
class FiltradorConfigManager : public sigc::trackable {
    public:
        FiltradorConfigManager(t_Filt tipo,
                              const filtradoresHandlers& handlers);
        ~FiltradorConfigManager();

        void desconectar();
        void reconectar();
// podría haber una señal que indique qué dimensión o hecho fue agregado o eliminado para actualizar todos los restantes combobox

//        sigc::signal< void, ConfigModelo* > signal_model_changed();
//        sigc::signal< void, ConfigModelo* > signal_model_saved();
//        sigc::signal< void, ConfigModelo* > signal_model_deleted();
    private:
//        sigc::signal< void, ConfigModelo* > _signal_model_changed;
//        sigc::signal< void, ConfigModelo* > _signal_model_saved;
//        sigc::signal< void, ConfigModelo* > _signal_model_deleted;

        t_Filt tipo;
        Gtk::VBox* pVBoxFiltradores;
        Gtk::ToolButton* pButtonAgregar;
        FiltradorConfigModelo* new_filtrador();

        /** conexiones a las señales */
        sigc::connection connectionButtonAgregar;

        void on_agregar_button_clicked();

// la lista sería del par < FiltradorConfigVista* , FiltradorConfigModelo* >,
// y el mapa de < id, par_anterior >
        typedef std::pair< FiltradorConfigVista*, FiltradorConfigModelo* > filtrador;
        std::list< filtrador > filtradores;
        // para una búsqueda más rápida
        std::map< unsigned,  filtrador > mapaFiltradores;
        bool guardandoCambios;
        static unsigned generadorID;
};

#endif  // FILTRADOR_CONFIG_MANAGER_H

