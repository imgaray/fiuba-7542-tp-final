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

class Tab : public Gtk::VBox {
    public:
        Tab(const Glib::ustring& etiqueta);
        ~Tab();

        Gtk::HBox& getEtiqueta();

        /** modelo */
        void agregarConsultante(FiltradorInputDimension* f);
        void agregarConsultante(Consultante* c);
        void removerConsultante(unsigned ID);

        void hacerConsulta(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);
        void recibirRespuesta(const Respuesta& rta);

        void informarConsultaIniciada();
        void informarConsultaTerminada();

        void agregarFiltroNavegable(FiltradorInput* f);

        void difundirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor);
        void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor);

        std::list< unsigned > getIDs();
        const std::map< unsigned, Consultante* >& getConsultantesFiltros();
    private:
        Gtk::HBox etiquetaCompuesta;
        Gtk::Label etiqueta;
        Gtk::Spinner spinner;

        /** modelo */
        std::map< unsigned, Consultante* > consultantes;
        std::map< unsigned, Consultante* > filtrosConsultantes;
        std::map< unsigned, Consultante* >* pConsultantesActivos;
        std::list< FiltradorInput* > filtrosNavegables;

        unsigned hijosActualizando;
        void correrSpinner();
        void detenerSpinner();
};

#endif  // TAB_H__
