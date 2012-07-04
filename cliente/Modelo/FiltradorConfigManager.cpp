#include "FiltradorConfigManager.h"
#include "FiltroConfigModelo.h"
#include "InputConfigModelo.h"
#include "PivoteXConfigModelo.h"
#include "PivoteYConfigModelo.h"
#include "ResultadoConfigModelo.h"
#include "FiltradorConfigVista.h"

unsigned FiltradorConfigManager::generadorID = 0;

FiltradorConfigManager::FiltradorConfigManager(t_Filt _tipo,
    const filtradoresHandlers& handlers)
: tipo(_tipo),
  pVBoxFiltradores(handlers.first),
  pButtonAgregar(handlers.second) {
    connectionButtonAgregar = pButtonAgregar->signal_clicked().connect(
        sigc::mem_fun(*this,
                      &FiltradorConfigManager::on_agregar_button_clicked));
}

FiltradorConfigManager::~FiltradorConfigManager() {
    std::list< filtrador >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it) {
        delete it->first;
        delete it->second;
    }
}

void FiltradorConfigManager::desconectar() {
    // remover los filtros de este manager
    std::list< filtrador >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        pVBoxFiltradores->remove(*(it->first));

    // desconectar la señal con el botón de agregar
    connectionButtonAgregar.disconnect();
}

void FiltradorConfigManager::reconectar() {
    // agregar los filtros de este manager
    std::list< filtrador >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        pVBoxFiltradores->pack_start(*(it->first), false, false);

    // reconectar la señal con el botón de agregar
    connectionButtonAgregar = pButtonAgregar->signal_clicked().connect(
        sigc::mem_fun(*this,
                      &FiltradorConfigManager::on_agregar_button_clicked));
}

FiltradorConfigModelo* FiltradorConfigManager::new_filtrador() {
    unsigned ID = generadorID++;

    switch (tipo) {
        case FILT_FILTRO: return new FiltroConfigModelo(ID);
        case FILT_INPUT: return new InputConfigModelo(ID);
        case FILT_PIVOTE_X: return new PivoteXConfigModelo(ID);
        case FILT_PIVOTE_Y: return new PivoteYConfigModelo(ID);
        case FILT_RESULTADO: return new ResultadoConfigModelo(ID);
        default: return NULL;
    }
}
#include <iostream>
void FiltradorConfigManager::on_agregar_button_clicked() {
    // creo el par vista/modelo
    FiltradorConfigModelo* filtModelo = new_filtrador();
    FiltradorConfigVista* filtVista = new FiltradorConfigVista(filtModelo);

    // conecto señales
    filtModelo->signal_delete_filtrador().connect(sigc::mem_fun(*this,
        &FiltradorConfigManager::on_delete_filtrador));

    // agrego a la vista
    pVBoxFiltradores->pack_start(*filtVista, false, false);

    // agrego a los contenedores
    filtrador f(filtVista, filtModelo);
    filtradores.push_back(f);
    mapaFiltradores[filtModelo->getID()] = f;
}

void FiltradorConfigManager::on_delete_filtrador(unsigned ID) {
    filtrador f = mapaFiltradores[ID];

    // busco en la lista y lo elimino
    std::list< filtrador >::iterator it = filtradores.begin();
    bool encontrado = false;
    while (!encontrado && it != filtradores.end())
        encontrado =  (*(it++)) == f;

    if (encontrado) {
        std::cout << "encontrado el filtrador de id: " << ID << ", removiéndolo" <<std::endl;
        filtradores.erase(--it);
    }

    // lo saco de la vista
    pVBoxFiltradores->remove(*(f.first));

    // libero memoria
    delete f.first;
    delete f.second;

    // lo saco del mapa
    mapaFiltradores.erase(ID);
}
