#ifndef TAB_H__
#define TAB_H__

#include <map>
#include <list>
#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/spinner.h>

class ServidorRemoto;
class Consultante;
class Respuesta;
class FiltradorInput;
class FiltradorInputDimension;
class VentanaClienteDinamica;

/** @class Tab
 * Pestaña concreta configurada por el admin.
 *
 * Es un conjunto de paneles, cada uno con sus particularidades de
 * filtradores y consultantes. Los distribuye en una matriz según la posición
 * configurada de cada uno. Agrega además unos inputs que se aplican a todas
 * las consultas de la tab.
 *
 * En cuanto al modelo, tiene dos mapas de consultantes, uno para los
 * filtradores que necesiten popular su combobox consultando los valores
 * posibles a la base de datos, y el otro es para los consultantes concretos,
 * es decir, tablas y gráficos. Cada vez que se le solicita que actualice,
 * itera a través del mapa activo de consultantes.
 *
 * El mapa activo es, por defecto, el de filtradores.
 * Cuando un filtrador recibe su respuesta informa a la tab que puede ser
 * removido del mapa, dado que sólo se actualizan una vez durante la
 * aplicación. Si este mapa llega a cero elementos, el otro pasa a ser el mapa
 * activo.
 */
class Tab : public Gtk::VBox {
    public:
        /**
         * Constructor.
         * @param etiqueta título de la pestaña
         */
        Tab(const Glib::ustring& etiqueta);
        /**
         * Destructor.
         */
        ~Tab();

        Gtk::HBox& getEtiqueta();

        /* modelo */
        /** Agrega un filtrador consultante al mapa de filtradores consultantes
         */
        void agregarConsultante(FiltradorInputDimension* f);

        /** Agrega un consultante concreto al mapa de consultantes normales
         */
        void agregarConsultante(Consultante* c);
        void removerConsultante(unsigned ID);

        /** Realiza las consultas del grupo de consultantes activos.
         */
        void hacerConsulta(ServidorRemoto& server);

        /** Cancela las consultas del grupo de consultantes activos.
         */
        void cancelarConsulta(ServidorRemoto& server);

        /** Actualiza una consulta en particular, a pedido.
         */
        void actualizarConsulta(Consultante* c);

        /** Informar a la pestaña que un consultante suyo está actualizando.
         */
        void informarConsultaIniciada();

        /** Informar a la pestaña que un consultante suyo terminó de
         *  actualizar.
         */
        void informarConsultaTerminada();

        /** Informar a la pestaña que no le agregarán nada.
         */
        void informarFinCreacion();

        void agregarFiltroNavegable(FiltradorInput* f);

        /** Informa a todos los filtros navegables la navegación seleccionada.
         */
        void difundirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor);

        const std::map< unsigned, Consultante* >& getConsultantes();
        void setPadre(VentanaClienteDinamica* padre);
    private:
        Gtk::HBox etiquetaCompuesta;
        Gtk::Label etiqueta;
        Gtk::Spinner spinner;

        /* modelo */
        std::map< unsigned, Consultante* > consultantes;
        std::map< unsigned, Consultante* > filtrosConsultantes;
        std::map< unsigned, Consultante* >* pConsultantesActivos;
        std::list< FiltradorInput* > filtrosNavegables;

        unsigned hijosActualizando;
        void correrSpinner();
        void detenerSpinner();
        VentanaClienteDinamica* padre;
};

#endif  // TAB_H__
