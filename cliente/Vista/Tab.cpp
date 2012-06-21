#include "Tab.h"
#include "FiltradorInputDimension.h"
#include "Respuesta.h"
#include <iostream>
#include <cassert>

Tab::Tab(const Glib::ustring& _etiqueta): etiqueta(_etiqueta) {
    etiquetaCompuesta.pack_end(etiqueta, false, false);
    etiquetaCompuesta.pack_end(spinner, false, false);
    etiqueta.show();
    spinner.hide();

    pConsultantesActivos = &filtrosConsultantes;
    hijosActualizando = 0;
}


Tab::~Tab() {}

Gtk::HBox& Tab::getEtiqueta() {
    return etiquetaCompuesta;
}


void Tab::agregarFiltroConsultante(FiltradorInputDimension* f) {
    filtrosConsultantes[f->getID()] = f;
    std::cout << this << " agregado filtro: id = " << f->getID() << ", dimensión = " << f->getFiltro() << std::endl;
    f->setPadre(this);
}

void Tab::agregarConsultante(Consultante* c) {
    consultantes[c->getID()] = c;
    c->setPadre(this);
}

void Tab::removerConsultante(unsigned ID) {
    unsigned tt = pConsultantesActivos->size();
    pConsultantesActivos->erase(pConsultantesActivos->find(ID));
    unsigned ttNuevo = pConsultantesActivos->size();
    bool consultanteInexistente = tt != ttNuevo;
    assert(consultanteInexistente);

    if (ttNuevo == 0)
        pConsultantesActivos = &consultantes;
}

void Tab::hacerConsulta(ServidorRemoto& server) {
    std::cout << "Haciendo consultas..." << std::endl;
}

void Tab::cancelarConsulta(ServidorRemoto& server) {
    std::cout << "Cancelando consultas..." << std::endl;
}

void Tab::recibirRespuesta(const Respuesta& rta) {
    std::cout << "Recibiendo respuesta id: " << rta.devolverID() << " . Pasando al consultante." << std::endl;
}

void Tab::informarConsultaIniciada() {
    ++hijosActualizando;
}

void Tab::informarConsultaTerminada() {
    --hijosActualizando;
}

void Tab::difundirNavegacionSeleccionada(const Glib::ustring& input,
                                         const Glib::ustring& valor) {
    std::cout << "Difundiendo navegación seleccionada..." << std::endl;
}

void Tab::recibirNavegacionSeleccionada(const Glib::ustring& input,
                                        const Glib::ustring& valor) {
    std::cout << "Recibiendo navegación seleccionada..." << std::endl;
}

std::list< unsigned > Tab::getIDs() {
    std::list< unsigned > ids;

    return ids;
}

const std::map< unsigned, Consultante* >& Tab::getConsultantesFiltros() {
    return filtrosConsultantes;
}

void Tab::correrSpinner() {
    spinner.show();
    spinner.start();
}

void Tab::detenerSpinner() {
    spinner.stop();
    spinner.hide();
}

