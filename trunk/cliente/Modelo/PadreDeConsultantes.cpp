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

    if (hijosActualizando > 0) {
        correrSpinner();
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

    if (hijosActualizando == 0) {
        detenerSpinner();
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

void PadreDeConsultantes::difundirNavegacionSeleccionada(
    const Glib::ustring& valor) {
    std::cout << "Difundiendo " << valor << std::endl;
}

void PadreDeConsultantes::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    std::cout << "Recibido input ( " << input << ", " << valor << ")" << std::endl;
}

void PadreDeConsultantes::setPadre(PadreDeConsultantes* _padre) {
    padre = _padre;
}

void PadreDeConsultantes::setSpinner(Gtk::Spinner* s) {
    spinner = s;
}

void PadreDeConsultantes::correrSpinner() {
    if (spinner) {
        spinner->show();
        spinner->start();
    }
}

void PadreDeConsultantes::detenerSpinner() {
    if (spinner) {
        spinner->stop();
        spinner->hide();
    }
}
