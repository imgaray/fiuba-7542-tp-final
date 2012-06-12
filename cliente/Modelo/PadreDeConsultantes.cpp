#include "PadreDeConsultantes.h"
#include "Consultante.h"

PadreDeConsultantes::PadreDeConsultantes() {
    spinner = NULL;
    padre = NULL;
    hijosActualizando = 0;
    difusor = false;
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

/** Si ya era el difusor, no emite la señal porque, por alguna razón,
 * no le llegó a sí mismo la suya propia.
 */
void PadreDeConsultantes::difundirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    std::cout << this << " comenzando difusión input ( " << input << ", " << valor << ")" << std::endl;
    if (!difusor) {
        std::cout << this << " difundiendo input ( " << input << ", " << valor << ")" << std::endl;
        difusor = true;
        padre->recibirNavegacionSeleccionada(input, valor);
    }
}

/** Si era el difusor, no se le aplica la opción seleccionada.
 * Luego de recibir su propia señal, puede asumir que ya fue difundida
 * a todos sus hermanos, y corta la señal con difusor = false
 */
void PadreDeConsultantes::recibirNavegacionSeleccionada(
    const Glib::ustring& input, const Glib::ustring& valor) {
    std::cout << this << " recibiendo input ( " << input << ", " << valor << ")" << std::endl;
    if (!difusor) {
        std::cout << this << " recibido input, difundiendo a hijos ( " << input << ", " << valor << ")" << std::endl;

        std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
        for ( ; it != hijos.end(); ++it)
            (*it)->recibirNavegacionSeleccionada(input, valor);
    }
    else
        std::cout << this << " era propio. Difundido input ( " << input << ", " << valor << ")" << std::endl;

    difusor = false;
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
