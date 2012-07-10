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
        void agregarConsultante(FiltradorInputDimension* f);
        void agregarConsultante(Consultante* c);
        void removerConsultante(unsigned ID);

        void hacerConsulta(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);
        // actualiza una consulta en particular, a pedido
        void actualizarConsulta(Consultante* c);

        void informarConsultaIniciada();
        void informarConsultaTerminada();
        void informarFinCreacion();

        void agregarFiltroNavegable(FiltradorInput* f);

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
