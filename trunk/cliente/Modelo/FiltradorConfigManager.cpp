#include "FiltradorConfigManager.h"
#include <algorithm>
#include "FiltroConfigModelo.h"
#include "InputConfigModelo.h"
#include "PivoteXConfigModelo.h"
#include "PivoteYConfigModelo.h"
#include "ResultadoConfigModelo.h"
#include "FiltradorConfigVista.h"
#include "Organizacion.h"


#define TOOLTIPO_BOTON_AGREGAR "No hay más campos para agregar"

#define NOMBRE_NODO "Filtrador_Config_Manager"
#define ATR_TIPO "atr_tipo"


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

void FiltradorConfigManager::setFiltradoresEn(FiltradoresTab* filtTab) {
    std::list< filtrador >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        it->second->setFiltradorEn(filtTab);
}

void FiltradorConfigManager::setFiltradoresEn(FiltradoresPanel* filtPanel) {
    std::list< filtrador >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        it->second->setFiltradorEn(filtPanel);
}

FiltradorConfigModelo* FiltradorConfigManager::new_filtrador() {
    std::list< std::string > camposDisponibles;
    std::string campo;
    for (unsigned i = 0; i < Organizacion::cantidadCampos(); ++i) {
        campo = Organizacion::nombreCampo(i);
        if (find(camposTomados.begin(), camposTomados.end(), campo)
                == camposTomados.end())
            camposDisponibles.push_back(campo);
    }

    if (camposDisponibles.size() == 0)
        return NULL;

    unsigned ID = generadorID++;

    switch (tipo) {
        case FILT_FILTRO:
            return new FiltroConfigModelo(ID, camposDisponibles);
        case FILT_INPUT:
            return new InputConfigModelo(ID, camposDisponibles);
        case FILT_PIVOTE_X:
            return new PivoteXConfigModelo(ID, camposDisponibles);
        case FILT_PIVOTE_Y:
            return new PivoteYConfigModelo(ID, camposDisponibles);
        case FILT_RESULTADO:
            return new ResultadoConfigModelo(ID, camposDisponibles);
        default: return NULL;
    }
}
#include <iostream>
void FiltradorConfigManager::on_agregar_button_clicked() {
    // crear el par vista/modelo
    FiltradorConfigModelo* filtModelo = new_filtrador();
    if (!filtModelo) {
        pButtonAgregar->set_sensitive(false);
        pButtonAgregar->set_tooltip_text(TOOLTIPO_BOTON_AGREGAR);
        return;
    }

    filtModelo->signal_campo_changed().connect(sigc::mem_fun(*this,
        &FiltradorConfigManager::on_filtrador_campo_changed));

    FiltradorConfigVista* filtVista = new FiltradorConfigVista(filtModelo);

    // conectar señales
    filtModelo->signal_delete_filtrador().connect(sigc::mem_fun(*this,
        &FiltradorConfigManager::on_delete_filtrador));

    // agregar a la vista
    pVBoxFiltradores->pack_start(*filtVista, false, false);

    // agregar a los contenedores
    filtrador f(filtVista, filtModelo);
    filtradores.push_back(f);
    mapaFiltradores[filtModelo->getID()] = f;
    ulitmoFilConfigModelo = filtModelo;
}

void FiltradorConfigManager::on_filtrador_campo_changed(
    Glib::ustring campoAnterior, Glib::ustring campoNuevo) {
    // remover el campo anterior
    if (campoAnterior != "") {
        std::list< std::string >::iterator it = find(camposTomados.begin(),
                                                     camposTomados.end(),
                                                     campoAnterior);
        if (it != camposTomados.end())
            camposTomados.erase(it);
    }
    // agregar el campo nuevo
    if (campoNuevo != "")
        camposTomados.push_back(campoNuevo);

    // informarle a todos los filtros que el campo nuevo ya no está disponible
    // y que el campo anterior volvió a estarlo
    std::list< filtrador >::iterator itFilt = filtradores.begin();
    for ( ; itFilt != filtradores.end(); ++itFilt)
        itFilt->second->actualizarCampos(campoNuevo, campoAnterior);
}

void FiltradorConfigManager::on_delete_filtrador(unsigned ID) {
    filtrador f = mapaFiltradores[ID];

    // buscar en la lista y eliminarlo
    std::list< filtrador >::iterator it = filtradores.begin();
    bool encontrado = false;
    while (!encontrado && it != filtradores.end())
        encontrado =  (*(it++)) == f;

    if (encontrado)
        filtradores.erase(--it);

    // sacarlo de la vista
    pVBoxFiltradores->remove(*(f.first));
    pButtonAgregar->set_sensitive(true);
    pButtonAgregar->set_tooltip_text("");

    // liberar memoria
    delete f.first;
    delete f.second;

    // sacarlo del mapa
    mapaFiltradores.erase(ID);
}

NodoXml FiltradorConfigManager::serializar() {
	NodoXml nodo(NOMBRE_NODO);

	std::list< filtrador >::iterator it;

	int n_tipo = this->tipo;

	nodo.SetAttribute(ATR_TIPO, n_tipo);

	for (it = filtradores.begin(); it != filtradores.end(); ++it) {
		nodo.InsertEndChild(it->second->serializar());
	}

	return nodo;
}
void FiltradorConfigManager::deserializar(const NodoXml& nodo) {

	int n_tipo = 0;
	if (!nodo.Attribute(ATR_TIPO, &n_tipo)) {
		throw ErrorSerializacionXML();
	}

	tipo = t_Filt (n_tipo);

	const NodoXml *nodoHijo = nodo.FirstChildElement();

	for (; nodoHijo != NULL ; nodoHijo = nodoHijo->NextSiblingElement()) {
		on_agregar_button_clicked();
		if (ulitmoFilConfigModelo != NULL)
			ulitmoFilConfigModelo->deserializar(*nodoHijo);
		else
			throw ErrorSerializacionXML();
	}
}
