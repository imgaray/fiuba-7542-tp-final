#include "VentanaClienteDinamica.h"
#include <cassert>
#include "Tab.h"
#include "Consultante.h"
#include "ExcepcionConsultanteNoExiste.h"
#include "ServidorRemoto.h"
#include <iostream>

#define CANT_MAX_RESP_PROC 10

VentanaClienteDinamica::VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder)
    : Gtk::Notebook(cobject) {}

VentanaClienteDinamica::~VentanaClienteDinamica() {}

void VentanaClienteDinamica::personalizar(const char* archivo) {
    if (!dynBuilder.personalizarDesdeArchivo(archivo)) {
        std::cout << "Error al abrir el archivo de personalización " << archivo
                  << ". Contáctese con el administrador." << std::endl;
        return;
    }

    unsigned i = 0;
    while (dynBuilder.tieneSiguiente()) {
        Tab& t = dynBuilder.siguiente();
        agregarData(&t, i++);
        append_page(t, t.getEtiqueta());
    }
}

void VentanaClienteDinamica::hacerConsultaFiltros(ServidorRemoto& server) {
    std::cout << "Popular combobox" << std::endl;
    std::map< unsigned, Consultante* >::iterator it = filtros.begin();
    for ( ; it != filtros.end(); ++it)
        it->second->hacerConsulta(server);
}

void VentanaClienteDinamica::hacerConsulta(ServidorRemoto& server) {
    tabs[get_current_page()]->hacerConsulta(server);
}

void VentanaClienteDinamica::cancelarConsulta(ServidorRemoto& server) {
    std::cout << "cancelar consultas de la tab activa" << std::endl;

}

void VentanaClienteDinamica::agregarData(Tab* t, unsigned i) {
    // Mapa de consultas (par ID consulta, i-tab)
    std::list< unsigned > idsConsultantes = t->getIDs();
    std::list< unsigned >::iterator it = idsConsultantes.begin();
    for ( ; it != idsConsultantes.end(); ++it)
        consultas[*it] = i;

    // Mapa de filtros con consulta
    std::map< unsigned, Consultante* > filtrosTab = t->getConsultantesFiltros();
    filtros.insert(filtrosTab.begin(), filtrosTab.end());

    // Tab
    tabs.push_back(t);
}

void VentanaClienteDinamica::retirarRespuestasFiltros(ServidorRemoto& server) {
    bool hayRespuestas = server.cantidadRespuestas() > 0;
    Respuesta resp;
    std::map< unsigned, Consultante* >::iterator it;
    bool consultanteExistente;

    for (int i = 0; i < CANT_MAX_RESP_PROC && hayRespuestas ; i++) {
        resp = server.obtenerRespuesta();
        it = filtros.find(resp.devolverID());
        consultanteExistente = it != filtros.end();
        assert(consultanteExistente);

        it->second->recibirRespuesta(resp);

        hayRespuestas = server.cantidadRespuestas() > 0;
    }
    if (filtros.size() == 0)
        std::cout << "Terminé con los filtros" << std::endl;
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

        tabs[it->second]->recibirRespuesta(resp);

        hayRespuestas = server.cantidadRespuestas() > 0;
    }
}
