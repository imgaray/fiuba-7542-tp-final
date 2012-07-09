#ifndef CONSULTANTE_H
#define CONSULTANTE_H

#include <gtkmm/spinner.h>
#include "Consulta.h"
#include "VerificadorConsultasH.h"

class Respuesta;
class ServidorRemoto;
class PadreDeConsultantes;
class Tab;
class FiltradoresPanel;

class Consultante {
    public:
        Consultante();
        Consultante(FiltradoresPanel* f);
        ~Consultante();

        virtual void hacerConsulta(ServidorRemoto& server);
        virtual void cancelarConsulta(ServidorRemoto& server);
        virtual void recibirRespuesta(const Respuesta& rta);

        virtual unsigned getID() const;

        FiltradoresPanel* getFiltrador() const;

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
        FiltradoresPanel* f;
        static unsigned generadorID;
        unsigned ID;
        bool esperandoRespuesta;
};

#endif  // CONSULTANTE_H
