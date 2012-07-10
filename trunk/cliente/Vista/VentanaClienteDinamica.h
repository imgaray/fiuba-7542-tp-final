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


/** @class VentanaClienteDinamica
 * Sector configurable de la aplicación. Se llama ventana pero en realidad es
 * un notebook.
 *
 * Gráficamente no tiene nada estático, con lo cual, sus métodos reflejan
 * el comportamiento de la resolución de consultas.
 *
 * Tiene un mapa con todos los consultantes presentes en la aplicación para
 * poder derivar directamente las respuestas, dado que es esta clase quien las
 * retira del servidor (a través del proxy ServidorRemoto).
 */
class VentanaClienteDinamica : public Gtk::Notebook, public Buildable  {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
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
