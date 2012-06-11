#ifndef FILTRADOR_INPUT_DIMENSION_H
#define FILTRADOR_INPUT_DIMENSION_H

#include "FiltradorInput.h"
#include "Consultante.h"
#include <gtkmm/spinner.h>

class Respuesta;

class FiltradorInputDimension : public FiltradorInput, public Consultante {
    public:
        FiltradorInputDimension(const Glib::ustring& input,
                                PadreDeConsultantes* padre);
        ~FiltradorInputDimension();

        Consulta& filtrar(Consulta& c);

    private:
        void procesarRespuesta(const Respuesta& rta);
        Gtk::Spinner s;
};

#endif  // FILTRADOR_INPUT_DIMENSION_H
