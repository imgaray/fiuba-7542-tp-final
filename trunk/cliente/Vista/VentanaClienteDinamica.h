#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <map>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include "Personalizador.h"

class Tab;
class ServidorRemoto;
class Consultante;

typedef std::map < unsigned, Consultante* > MapaConsultantesTab;
typedef std::pair < unsigned, Consultante* > parMapaConsultas;

class VentanaClienteDinamica : public Gtk::Notebook {
    public:
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(const char* archivo);

        void hacerConsulta(ServidorRemoto& server);
        void hacerConsultaInicial(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);

        void removerConsultante(unsigned ID);
        void agregarConsultantesTab(const MapaConsultantesTab& consultantes);

        void retirarRespuestas(ServidorRemoto& server);

        bool disponibleParaActualizacion(guint pag);

    private:
        Personalizador dynBuilder;
        MapaConsultantesTab consultas;
        std::vector< Tab* > tabs;

        void agregarData(Tab& t);
};

#endif  // VENTANA_CLIENTE_DINAMICA_H
