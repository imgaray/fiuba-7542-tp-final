#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include "PadreDeConsultantes.h"
#include "Personalizador.h"
#include "../../comun/Definiciones.h"
#include <map>

typedef std::map < Id_Mensaje, Consultante* > MapaConsultantesNB;
typedef std::pair < Id_Mensaje, Consultante* > parMapaConsultas;

class VentanaClienteDinamica
: public Gtk::Notebook, public PadreDeConsultantes {
    public:
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(const char* archivo);

        void hacerConsulta(ServidorRemoto& server);

        void agregarConsultanteConcreto(Consultante *cons);

        Consultante* devolverConsultante(Id_Mensaje id);
    private:
        Personalizador dynBuilder;
        MapaConsultantesNB _mConsultas;
};

#endif  // VENTANA_CLIENTE_DINAMICA_H
