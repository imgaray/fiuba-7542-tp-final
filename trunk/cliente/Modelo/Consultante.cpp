#include "Consultante.h"
#include "Respuesta.h"
#include <iostream>
#include "Consulta.h"
#include "ServidorRemoto.h"
#include "Tab.h"
#include "FiltradoresPanel.h"

unsigned Consultante::generadorID = 0;

Consultante::Consultante() : f(NULL){
    ID = generadorID++;
    esperandoRespuesta = false;
    consulta.definirID(ID);
}

Consultante::Consultante(FiltradoresPanel* _f) : f(_f){
    ID = generadorID++;
    esperandoRespuesta = false;
    consulta.definirID(ID);
}

Consultante::~Consultante() {}

void Consultante::setPadre(Tab* _padre) {
    padre = _padre;
}

void Consultante::hacerConsulta(ServidorRemoto& server) {
    consulta.limpiar();

    // si hay filtradores, verificar que estén correctos:
    // comboboxes populados y entries bien escritas
    if (f) {
        if (!f->puedeFiltrar())
            return;
        f->filtrar(consulta);
    }

    if (!verificador.verificarConsulta(consulta)) {
        std::cout << "Error en consulta" << std::endl;
        return;
    }

    cancelarConsulta(server);

    esperandoRespuesta = true;
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

FiltradoresPanel* Consultante::getFiltrador() const {
    return f;
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
