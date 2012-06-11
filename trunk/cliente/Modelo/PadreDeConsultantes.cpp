#include "PadreDeConsultantes.h"
#include "Consultante.h"

PadreDeConsultantes::PadreDeConsultantes() {
    spinner = NULL;
    padre = NULL;
    hijosActualizando = 0;
}

void PadreDeConsultantes::hacerConsulta(ServidorRemoto& server) {
    if (hijosActualizando > 0)
        cancelarConsulta(server);

    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for ( ; it != hijos.end(); ++it)
        (*it)->hacerConsulta(server);

//    std::cout << "( " << this << ") Hijos actualizando: " << hijosActualizando << std::endl;

    if (hijosActualizando > 0) {
        if (spinner) {
            spinner->show();
            spinner->start();
        }
        if (padre)
            padre->informarConsultaIniciada();
    }
}

void PadreDeConsultantes::cancelarConsulta(ServidorRemoto& server) {
    if (hijosActualizando == 0)
        return;

    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for ( ; it != hijos.end(); ++it)
        (*it)->cancelarConsulta(server);

//    std::cout << "( " << this << ") Hijos actualizando: " << hijosActualizando << std::endl;

    if (hijosActualizando == 0) {
        if (spinner) {
            spinner->stop();
            spinner->hide();
        }
        if (padre)
            padre->informarConsultaTerminada();
    }
}

void PadreDeConsultantes::agregarConsultante(PadreDeConsultantes* c) {
    hijos.push_back(c);
    c->setPadre(this);
}


void PadreDeConsultantes::informarConsultaTerminada() {
    Lock l(m);
    --hijosActualizando;
}

void PadreDeConsultantes::informarConsultaIniciada() {
    Lock l(m);
    ++hijosActualizando;
}

void PadreDeConsultantes::setPadre(PadreDeConsultantes* _padre) {
    padre = _padre;
}

void PadreDeConsultantes::setSpinner(Gtk::Spinner* s) {
    spinner = s;
}
