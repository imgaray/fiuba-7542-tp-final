#include "PadreDeConsultantes.h"
#include "Consultante.h"

PadreDeConsultantes::PadreDeConsultantes() {
    spinner = NULL;
    padre = NULL;
    hijosActualizando = 0;
}

void PadreDeConsultantes::hacerConsulta(ServidorRemoto& server) {
    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for ( ; it != hijos.end(); ++it)
        (*it)->hacerConsulta(server);

    Lock l(m);
    /** @todo revisar esta línea, porque la lógica dice que debería ser
     * ++hijosActualizando en cada iteración del for anterior */
    hijosActualizando = hijos.size();
    if (hijosActualizando > 0) {
        std::cout << "Hijos actualizando: " << hijosActualizando << std::endl;
        if (spinner) {
            spinner->show();
            spinner->start();
        }
    }
}

void PadreDeConsultantes::cancelarConsulta(ServidorRemoto& server) {
    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for ( ; it != hijos.end(); ++it)
        (*it)->cancelarConsulta(server);

    std::cout << "Hijos actualizando: " << hijosActualizando << std::endl;


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
    Consultante* cons = dynamic_cast< Consultante* >(c);
    if (cons)
        std::cout << "Agregado consultante ID: " << cons->getID() << std::endl;
    else
        std::cout << "Agregado un padre de consultantes" << std::endl;
}


void PadreDeConsultantes::informarConsultaTerminada() {
    Lock l(m);
    --hijosActualizando;

    if (hijosActualizando == 0) {
        if (spinner) {
            spinner->stop();
            spinner->hide();
        }
        if (padre)
            padre->informarConsultaTerminada();
    }
}

void PadreDeConsultantes::setPadre(PadreDeConsultantes* _padre) {
    std::cout << _padre << " es ahora padre de " << this << std::endl;
    padre = _padre;
}

void PadreDeConsultantes::setSpinner(Gtk::Spinner* s) {
    spinner = s;
}
