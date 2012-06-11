#include "FiltradorInput.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorInput::FiltradorInput(const Glib::ustring& input)
: Filtrador(input) {
    centradorDerecho.pack_end(sep, false, false);
    centradorDerecho.pack_end(valores, false, false);
}

FiltradorInput::~FiltradorInput() {}

