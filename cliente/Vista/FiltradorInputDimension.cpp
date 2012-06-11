#include "FiltradorInputDimension.h"

FiltradorInputDimension::FiltradorInputDimension(const Glib::ustring& input,
    PadreDeConsultantes* padre) : FiltradorInput(input) {
    padre->agregarConsultante(this);
    padre->setSpinner(&s);
    centradorDerecho.pack_start(s, false, false);
    s.hide();
}

FiltradorInputDimension::~FiltradorInputDimension() {}

void FiltradorInputDimension::procesarRespuesta(const Respuesta& rta) {
//    if (padre)
//        padre->setSpinner(&s);
}
