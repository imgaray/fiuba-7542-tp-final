#ifndef CONSULTANTE_H
#define CONSULTANTE_H

#include <gtkmm/spinner.h>
#include "Consulta.h"
#include "VerificadorConsultasH.h"

class Respuesta;
class ServidorRemoto;
class PadreDeConsultantes;
class Tab;

class Consultante {
    public:
        Consultante();
        ~Consultante();

        virtual void hacerConsulta(ServidorRemoto& server);
        virtual void cancelarConsulta(ServidorRemoto& server);
        virtual void recibirRespuesta(const Respuesta& rta);

        virtual unsigned getID() const;

        void setSpinner(Gtk::Spinner* s);
        void setPadre(Tab* padre);
        void on_navegabilidad_seleccionada();
    protected:
        Consulta consulta;
        virtual void procesarRespuesta(const Respuesta& rta) = 0;
        Tab* padre;
        Gtk::Spinner* spinner;
        void correrSpinner();
        void detenerSpinner();
    private:
        VerificadorConsultasH verificador;
        static unsigned generadorID;
        unsigned ID;
        bool esperandoRespuesta;
};

#endif  // CONSULTANTE_H
