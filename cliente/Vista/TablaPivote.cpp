/*
 * TablaPivote.cpp
 *
 *  Created on: 23/06/2012
 *      Author: migue
 */

#include "TablaPivote.h"
#include "Respuesta.h"
#include "Consulta.h"

TablaPivote::TablaPivote(FiltradoresPanel& filtradores) : Tabla(filtradores) {

}

TablaPivote::~TablaPivote() {

}

void TablaPivote::hacerConsulta(ServidorRemoto& server) {
//    Consulta& c = getConsulta();
    consulta.limpiar();
    consulta.definirConsultaDeTablaPivote();
    _filtradores.filtrar(consulta);
    Consultante::hacerConsulta(server);
}

void TablaPivote::procesarRespuesta(const Respuesta& rta) {

	if (_colModelo != NULL) {
		this->remove_all_columns();
		delete _colModelo;
		//_refTreeModel.clear();
	}

	_colModelo = new ColumnasModelo(rta.cantidadColumnas());

	 _refTreeModel = Gtk::ListStore::create(*_colModelo);
	 this->set_model(_refTreeModel);


	 for (unsigned i = 0; i < rta.cantidadFilas() ; i++) {
		 agregarFila(i, rta);
	 }

	agregarColumnas();

}

void TablaPivote::agregarFila(int numFila, const Respuesta& resp) {
	 Gtk::TreeModel::Row filaNueva = *(_refTreeModel->append());

	 for (unsigned i = 0; i < resp.cantidadColumnas() ; i++) {
		 filaNueva[_colModelo->_columnas[i]] = resp.dato(numFila, i);
	 }
}

void TablaPivote::agregarColumnas() {
	for (int i = 0; i < _colModelo->_cantCol ; i++) {
		//this->append_column(this->consulta.resultado(i),_colModelo->_columnas[i] );
		this->append_column("", _colModelo->_columnas[i] );
	}
}

