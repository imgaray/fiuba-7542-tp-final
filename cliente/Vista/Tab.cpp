#include "Tab.h"
#include "FiltradorInputDimension.h"
#include "VentanaClienteDinamica.h"
#include "Respuesta.h"
#include <cassert>

Tab::Tab(const Glib::ustring& _etiqueta)
: etiqueta(_etiqueta), padre(NULL) {
    etiquetaCompuesta.pack_start(spinner, false, false);
    etiquetaCompuesta.pack_start(etiqueta, false, false);
    etiqueta.show();
    spinner.hide();
    spinner.set_no_show_all();

    pConsultantesActivos = &filtrosConsultantes;
    hijosActualizando = 0;
}


Tab::~Tab() {}

Gtk::HBox& Tab::getEtiqueta() {
    return etiquetaCompuesta;
}

void Tab::agregarConsultante(FiltradorInputDimension* f) {
    filtrosConsultantes[f->getID()] = f;
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
        pConsultantesActivos = &consultantes;
        padre->agregarConsultantesTab(*pConsultantesActivos);
    }
}

void Tab::hacerConsulta(ServidorRemoto& server) {
    std::map< unsigned, Consultante* >::iterator it;
    for (it = pConsultantesActivos->begin(); it != pConsultantesActivos->end(); ++it)
        it->second->hacerConsulta(server);
}

void Tab::cancelarConsulta(ServidorRemoto& server) {
    std::map< unsigned, Consultante* >::iterator it;
    for (it = pConsultantesActivos->begin(); it != pConsultantesActivos->end(); ++it)
        it->second->cancelarConsulta(server);
}

void Tab::actualizarConsulta(Consultante* c) {
    padre->actualizarConsulta(c);
}

void Tab::informarConsultaIniciada() {
    ++hijosActualizando;
    if (hijosActualizando > 0)
        correrSpinner();
}

void Tab::informarConsultaTerminada() {
    --hijosActualizando;
    if (hijosActualizando == 0)
        detenerSpinner();
}

void Tab::informarFinCreacion() {
    if (filtrosConsultantes.size() == 0)
        pConsultantesActivos = &consultantes;
}

void Tab::agregarFiltroNavegable(FiltradorInput* f) {
    filtrosNavegables.push_back(f);
    f->setTabPadre(this);
}

void Tab::difundirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor) {
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
