#ifndef PADRE_DE_CONSULTANTES_H
#define PADRE_DE_CONSULTANTES_H

#include <gtkmm/spinner.h>
#include "Mutex.h"

class PadreDeConsultantes {
    public:
        PadreDeConsultantes();
        virtual void hacerConsulta();
        void informarConsultaTerminada();
    protected:
        void agregarConsultante(PadreDeConsultantes* c);
        void setSpinner(Gtk::Spinner* s);
    private:
        void setPadre(PadreDeConsultantes* padre);
        PadreDeConsultantes* padre;
        std::list< PadreDeConsultantes* > hijos;
        Mutex m;
        unsigned hijosActualizando;
        Gtk::Spinner* spinner;
};

#endif  // PADRE_DE_CONSULTANTES_H
