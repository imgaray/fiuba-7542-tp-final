#ifndef PADRE_DE_CONSULTANTES_H
#define PADRE_DE_CONSULTANTES_H

#include <gtkmm/spinner.h>
#include "Mutex.h"

class ServidorRemoto;

class PadreDeConsultantes {
    public:
        PadreDeConsultantes();

        virtual void hacerConsulta(ServidorRemoto& server);
        virtual void cancelarConsulta(ServidorRemoto& server);

        void informarConsultaIniciada();
        void informarConsultaTerminada();

        virtual void difundirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor);
        virtual void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor);

        void agregarConsultante(PadreDeConsultantes* c);
        void setSpinner(Gtk::Spinner* s);
    protected:
        PadreDeConsultantes* padre;
        void correrSpinner();
        void detenerSpinner();
    private:
        void setPadre(PadreDeConsultantes* padre);
        std::list< PadreDeConsultantes* > hijos;
        Mutex m;
        unsigned hijosActualizando;
        Gtk::Spinner* spinner;
        bool difusor;
};

#endif  // PADRE_DE_CONSULTANTES_H
