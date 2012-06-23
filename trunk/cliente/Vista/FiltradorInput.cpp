#include "FiltradorInput.h"
#include "ExcepcionFiltradorMalConstruido.h"

FiltradorInput::FiltradorInput(const Glib::ustring& input)
: Filtrador(input) {
    centradorDerecho.pack_start(sep, false, false);
    centradorDerecho.pack_start(valores, false, false);
    valido = false;
}

FiltradorInput::~FiltradorInput() {}

void FiltradorInput::setTabPadre(Tab* padre) {
    tabPadre = padre;
}

sigc::signal< void > FiltradorInput::signal_navegabilidad() {
    return signal_navegabilidad_seleccionada;
}
