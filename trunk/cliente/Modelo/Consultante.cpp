#include "Consultante.h"
#include "Respuesta.h"
#include <iostream>
#include "Consulta.h"
#include "ServidorRemoto.h"
#include "Tab.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() {
    ID = generadorID++;
    esperandoRespuesta = false;
    consulta.definirID(ID);
}

Consultante::~Consultante() {}

void Consultante::setPadre(Tab* _padre) {
    padre = _padre;
}

void Consultante::hacerConsulta(ServidorRemoto& server) {
    cancelarConsulta(server);

    esperandoRespuesta = true;
std::cout << "void Consultante::hacerConsulta(ServidorRemoto& server)... soy ID: " << ID << std::endl;
	server.enviarConsulta(this, consulta);
    padre->informarConsultaIniciada();
    correrSpinner();
}

void Consultante::cancelarConsulta(ServidorRemoto& server) {
    if (esperandoRespuesta) {
        server.cancelarConsulta(ID);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

void Consultante::recibirRespuesta(const Respuesta& rta) {
    if (esperandoRespuesta) {
        procesarRespuesta(rta);
        padre->informarConsultaTerminada();
        esperandoRespuesta = false;
        detenerSpinner();
    }
}

unsigned Consultante::getID() const {
    return ID;
}

void Consultante::on_navegabilidad_seleccionada() {
    padre->actualizarConsulta(this);
}

void Consultante::setSpinner(Gtk::Spinner* s) {
    spinner = s;
}

void Consultante::correrSpinner() {
    if (spinner) {
        spinner->show();
        spinner->start();
    }
}

void Consultante::detenerSpinner() {
    if (spinner) {
        spinner->stop();
        spinner->hide();
    }
}
