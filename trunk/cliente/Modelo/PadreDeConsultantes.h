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
        void informarConsultaTerminada();
        void agregarConsultante(PadreDeConsultantes* c);
        void setSpinner(Gtk::Spinner* s);
    protected:
        PadreDeConsultantes* padre;
    private:
        void setPadre(PadreDeConsultantes* padre);
        std::list< PadreDeConsultantes* > hijos;
        Mutex m;
        unsigned hijosActualizando;
        Gtk::Spinner* spinner;
};

#endif  // PADRE_DE_CONSULTANTES_H
