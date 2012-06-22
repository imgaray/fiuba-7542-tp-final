/*
 * TablaComun.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "TablaComun.h"



TablaComun::TablaComun(FiltradoresPanel& filtradores) : Tabla(filtradores) {

}

TablaComun::~TablaComun() {

}

void TablaComun::procesarRespuesta(const Respuesta& rta) {
	if (_colModelo != NULL)
		delete _colModelo;

	_colModelo = new ColumnasModelo(rta.cantidadColumnas());

	 _refTreeModel = Gtk::ListStore::create(_colModelo);
	 this->set_model(_refTreeModel);


	 for (int i = 0; i < rta.cantidadFilas() ; i++) {
		 agregarFila(i, resp);
	 }

	agregarColumnas();
}

void TablaComun::agregarFila(int numFila, const Respuesta& resp) {
	 Gtk::TreeModel::Row filaNueva = *(_refTreeModel->append());

	 for (int i = 0; i < resp.cantidadColumnas() ; i++) {
		 filaNueva[_colModelo->_columnas[i]] = resp.dato(numFila, i);
	 }
}


void TablaComun::agregarColumnas() {
	for (int i = 0; i < _colModelo->_cantCol ; i++) {
		this->append_column(this->consulta.resultado(i),_colModelo->_columnas[i] );
	}
}
