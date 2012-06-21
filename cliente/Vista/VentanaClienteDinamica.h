#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <map>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include "Personalizador.h"

class Tab;
class ServidorRemoto;
class Consultante;

typedef std::map < unsigned, unsigned > MapaConsultantesTab;
typedef std::pair < unsigned, unsigned > parMapaConsultasTab;

class VentanaClienteDinamica : public Gtk::Notebook {
    public:
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(const char* archivo);

        void hacerConsultaFiltros(ServidorRemoto& server);
        void hacerConsulta(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);

        bool retirarRespuestasFiltros(ServidorRemoto& server);
        void retirarRespuestas(ServidorRemoto& server);

    private:
        Personalizador dynBuilder;
        MapaConsultantesTab consultas;
        std::map< unsigned, Consultante* > filtros;
        std::vector< Tab* > tabs;

        void agregarData(Tab* t, unsigned i);
};

#endif  // VENTANA_CLIENTE_DINAMICA_H
