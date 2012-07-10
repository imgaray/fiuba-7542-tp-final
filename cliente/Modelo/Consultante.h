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


/** @class Consultante
 * Clase capaz de armar consultas y enviarlas al servidor que se le solicite.
 *
 * Es el modelo de conexión detrás de las tablas y gráficos y el input por
 * dimensión. Controla también el estado de los Gtk::Spinners, un widget
 * informativo para indicar que se espera una respuesta del servidor.
 */
class Consultante {
    public:
        Consultante();
        Consultante(FiltradoresPanel* f);
        ~Consultante();

        void hacerConsulta(ServidorRemoto& server);
        void cancelarConsulta(ServidorRemoto& server);
        void recibirRespuesta(const Respuesta& rta);

        unsigned getID() const;

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
