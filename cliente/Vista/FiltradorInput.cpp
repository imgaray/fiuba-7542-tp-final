#include "FiltradorInput.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorInput::FiltradorInput(const Glib::ustring& input)
: Filtrador(input) {
    centradorDerecho.pack_start(sep, false, false);
    centradorDerecho.pack_start(valores, false, false);
}

FiltradorInput::~FiltradorInput() {}
