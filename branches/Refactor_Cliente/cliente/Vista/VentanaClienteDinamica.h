#ifndef VENTANA_CLIENTE_DINAMICA_H
#define VENTANA_CLIENTE_DINAMICA_H

#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include "PadreDeConsultantes.h"
#include "Personalizador.h"

class VentanaClienteDinamica
: public Gtk::Notebook, public PadreDeConsultantes {
    public:
        VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder);
        ~VentanaClienteDinamica();

        void personalizar(const char* archivo);

        void hacerConsulta(ServidorRemoto& server);

    private:
        Personalizador dynBuilder;
};

#endif  // VENTANA_CLIENTE_DINAMICA_H
