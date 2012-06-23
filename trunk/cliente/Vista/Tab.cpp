#include "Tab.h"
#include "FiltradorInputDimension.h"
#include "VentanaClienteDinamica.h"
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
    inputsDisponibles = 0;
    puedeActualizar = false;
}


Tab::~Tab() {}

Gtk::HBox& Tab::getEtiqueta() {
    return etiquetaCompuesta;
}


void Tab::agregarConsultante(FiltradorInputDimension* f) {
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

    padre->removerConsultante(ID);

    if (ttNuevo == 0) {
        std::cout << this << " no tengo más combobox para popular, cambio mi mapa de consultantes al de consultantes concretos" << std::endl;
        pConsultantesActivos = &consultantes;
        padre->agregarConsultantesTab(*pConsultantesActivos);
    }
}

void Tab::hacerConsulta(ServidorRemoto& server) {
    std::cout << "Haciendo consultas..." << std::endl;
    std::map< unsigned, Consultante* >::iterator it;
    for (it = pConsultantesActivos->begin(); it != pConsultantesActivos->end(); ++it)
        it->second->hacerConsulta(server);
}

void Tab::cancelarConsulta(ServidorRemoto& server) {
    std::cout << "Cancelando consultas..." << std::endl;
    std::map< unsigned, Consultante* >::iterator it;
    for (it = pConsultantesActivos->begin(); it != pConsultantesActivos->end(); ++it)
        it->second->cancelarConsulta(server);
}

void Tab::actualizarConsulta(Consultante* c) {
    padre->actualizarConsulta(c);
}

void Tab::informarConsultaIniciada() {
    ++hijosActualizando;
    std::cout << this << " hijos actualizando: " << hijosActualizando << std::endl;
    if (hijosActualizando > 0)
        correrSpinner();
}

void Tab::informarConsultaTerminada() {
    --hijosActualizando;
    std::cout << this << " hijos actualizando: " << hijosActualizando << std::endl;
    if (hijosActualizando == 0)
        detenerSpinner();
}

void Tab::informarInputDisponible() {
    ++inputsDisponibles;
    std::cout << this << " inputs disponibles: " << inputsDisponibles
                      << " inputs totales: " << filtrosNavegables.size() << std::endl;
    if (inputsDisponibles == filtrosNavegables.size()) {
        puedeActualizar = true;
        padre->refresh();
    }
}

void Tab::informarInputNoDisponible() {
    --inputsDisponibles;
    std::cout << this << " inputs disponibles: " << inputsDisponibles
                      << " inputs totales: " << filtrosNavegables.size() << std::endl;
    if (inputsDisponibles < filtrosNavegables.size()) {
        puedeActualizar = false;
        padre->refresh();
    }
}

void Tab::informarFinCreacion() {
    if (filtrosNavegables.size() == 0)
        puedeActualizar = true;
    if (filtrosConsultantes.size() == 0)
        pConsultantesActivos = &consultantes;
}

void Tab::agregarFiltroNavegable(FiltradorInput* f) {
    filtrosNavegables.push_back(f);
    f->setTabPadre(this);
}

bool Tab::disponibleParaActualizacion() {
    return puedeActualizar;
}

void Tab::difundirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor) {
    std::cout << this << " difundiendo navegación seleccionada... (@todo)" << std::endl;
    std::list< FiltradorInput* >::iterator it = filtrosNavegables.begin();
    for ( ; it != filtrosNavegables.end(); ++it)
        (*it)->recibirNavegacionSeleccionada(input, valor);
}

const std::map< unsigned, Consultante* >& Tab::getConsultantes() {
    return *pConsultantesActivos;
}

void Tab::correrSpinner() {
    spinner.show();
    spinner.start();
}

void Tab::detenerSpinner() {
    spinner.stop();
    spinner.hide();
}

void Tab::setPadre(VentanaClienteDinamica* _padre) {
    padre = _padre;
}
