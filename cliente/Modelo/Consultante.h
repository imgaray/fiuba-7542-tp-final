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
        /**
         * Constructor.
         */
        Consultante();
        /**
         * Constructor.
         * @param f conjunto de filtradores asociados
         */
        Consultante(FiltradoresPanel* f);
        /**
         * Destructor.
         */
        ~Consultante();

        /**
         * Envía la consulta, cancelando si ya estaba esperando una respuesta
         * e informa al padre para que pueda controlar su spinner.
         */
        void hacerConsulta(ServidorRemoto& server);

        /**
         * Cancela la consulta enviada, e informa al padre que no espera más
         * respuesta.
         */
        void cancelarConsulta(ServidorRemoto& server);

        /**
         * Si estaba esperando una respuesta, la procesa.
         */
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
