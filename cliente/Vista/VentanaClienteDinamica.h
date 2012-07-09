#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <map>
#include <gtkmm/notebook.h>
#include "Personalizador.h"
#include "Buildable.h"

class Tab;
class ServidorRemoto;
class Consultante;

typedef std::map < unsigned, Consultante* > MapaConsultantesTab;
typedef std::pair < unsigned, Consultante* > parMapaConsultas;

class VentanaClienteDinamica : public Gtk::Notebook, public Buildable  {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(Personalizador& dynBuilder);

        void hacerConsulta(ServidorRemoto& server);
        void hacerConsultaInicial(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);
        // actualiza una consulta en particular, a pedido
        void actualizarConsulta(Consultante* c);

        void removerConsultante(unsigned ID);
        void agregarConsultantesTab(const MapaConsultantesTab& consultantes);

        void retirarRespuestas(ServidorRemoto& server);

        sigc::signal< void, Consultante* > signal_actualizacion();

    private:
        MapaConsultantesTab consultas;
        std::vector< Tab* > tabs;

        void agregarData(Tab& t);

        sigc::signal< void, Consultante* > solicitudDeActualizacion;
};

#endif  // VENTANA_CLIENTE_DINAMICA_H
