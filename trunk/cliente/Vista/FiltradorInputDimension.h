#ifndef FILTRADOR_INPUT_DIMENSION_H
#define FILTRADOR_INPUT_DIMENSION_H

#include "FiltradorInput.h"
#include "Consultante.h"
#include <gtkmm/entry.h>

class Respuesta;

class FiltradorInputDimension : public FiltradorInput, public Consultante {
    public:
        FiltradorInputDimension(const Glib::ustring& input);
        ~FiltradorInputDimension();

    private:
        void procesarRespuesta(const Respuesta& rta);
};

#endif  // FILTRADOR_INPUT_DIMENSION_H
