#ifndef FILTRADOR_INPUT_DIMENSION_H
#define FILTRADOR_INPUT_DIMENSION_H

#include "FiltradorInput.h"
#include "Consultante.h"
#include <gtkmm/spinner.h>

class Respuesta;

/** @class FiltradorInputDimension
 * Input de comportamiento "básico", es decir, no es hecho ni fecha.
 */
class FiltradorInputDimension : public FiltradorInput, public Consultante {
    public:
        /**
         * Constructor.
         * @param input nombre de la dimensión elegida
         */
        FiltradorInputDimension(const Glib::ustring& input);
        /**
         * Destructor.
         */
        ~FiltradorInputDimension();

        void filtrar(Consulta& c);

        void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                           const Glib::ustring& valor);

    private:
        void procesarRespuesta(const Respuesta& rta);
        Gtk::Spinner s;
};

#endif  // FILTRADOR_INPUT_DIMENSION_H
