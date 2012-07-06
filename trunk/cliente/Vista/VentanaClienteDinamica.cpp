#include "VentanaClienteDinamica.h"
#include <cassert>
#include "Tab.h"
#include "Consultante.h"
#include "ExcepcionConsultanteNoExiste.h"
#include "ServidorRemoto.h"

#define CANT_MAX_RESP_PROC 10

VentanaClienteDinamica::VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& _builder)
    : Gtk::Notebook(cobject), Buildable(_builder) {}

VentanaClienteDinamica::~VentanaClienteDinamica() {}

#include <iostream>
void VentanaClienteDinamica::personalizar(Personalizador& dynBuilder) {
    std::vector< Tab* >::iterator it = tabs.begin();
    for ( ; it != tabs.end(); ++it)
        remove(**it);
    tabs.clear();
    consultas.clear();

    while (dynBuilder.tieneSiguiente()) {
        Tab& t = dynBuilder.siguiente();
        agregarData(t);
        append_page(t, t.getEtiqueta());
    }
    show_all();
}

void VentanaClienteDinamica::hacerConsulta(ServidorRemoto& server) {
    tabs[get_current_page()]->hacerConsulta(server);
}

void VentanaClienteDinamica::hacerConsultaInicial(ServidorRemoto& server) {
    MapaConsultantesTab::iterator it = consultas.begin();
    for ( ; it != consultas.end(); ++it)
        it->second->hacerConsulta(server);
}

void VentanaClienteDinamica::cancelarConsulta(ServidorRemoto& server) {
    tabs[get_current_page()]->cancelarConsulta(server);
}

void VentanaClienteDinamica::actualizarConsulta(Consultante* c) {
    solicitudDeActualizacion.emit(c);
}

void VentanaClienteDinamica::agregarData(Tab& t) {
    // Mapa de consultas
    agregarConsultantesTab(t.getConsultantes());

    // Set padre
    t.setPadre(this);

    // vector< Tab* >
    tabs.push_back(&t);
}

void VentanaClienteDinamica::removerConsultante(unsigned ID) {
    unsigned tt = consultas.size();
    consultas.erase(consultas.find(ID));
    unsigned ttNuevo = consultas.size();
    bool consultanteInexistente = tt != ttNuevo;
    assert(consultanteInexistente);
}

void VentanaClienteDinamica::agregarConsultantesTab(
    const MapaConsultantesTab& consultantes) {
    consultas.insert(consultantes.begin(), consultantes.end());
}

void VentanaClienteDinamica::retirarRespuestas(ServidorRemoto& server) {
    bool hayRespuestas = server.cantidadRespuestas() > 0;
    Respuesta resp;
    MapaConsultantesTab::iterator it;
    bool consultanteExistente;

    for (int i = 0; i < CANT_MAX_RESP_PROC && hayRespuestas ; i++) {
        resp = server.obtenerRespuesta();
        it = consultas.find(resp.devolverID());
        consultanteExistente = it != consultas.end();
        assert(consultanteExistente);

        it->second->recibirRespuesta(resp);

        hayRespuestas = server.cantidadRespuestas() > 0;
    }
}

bool VentanaClienteDinamica::disponibleParaActualizacion(guint pag) {
    return tabs[pag]->disponibleParaActualizacion();
}

void VentanaClienteDinamica::refresh() {
    int p = get_current_page();
    set_current_page(p-1);
    set_current_page(p);
}
sigc::signal< void, Consultante* > VentanaClienteDinamica::signal_actualizacion() {
    return solicitudDeActualizacion;
}
