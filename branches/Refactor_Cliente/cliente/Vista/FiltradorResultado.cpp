#include "FiltradorResultado.h"

FiltradorResultado::FiltradorResultado(const Glib::ustring& _resultado)
:Filtrador("Resultado: "), resultado(_resultado) {
    centradorDerecho.pack_start(resultado, false, false);
}

FiltradorResultado::~FiltradorResultado() {}

void FiltradorResultado::setResultado(const Glib::ustring& _resultado) {
    resultado.set_text(_resultado);
}

Glib::ustring FiltradorResultado::getResultado() {
    return resultado.get_text();
}
