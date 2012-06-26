/*
 * TablaComun.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "TablaComun.h"
#include "Tab.h"
#include <iostream>
#include <string>

TablaComun::TablaComun(FiltradoresPanel& filtradores) : Tabla(filtradores) {

	this->signal_row_activated().connect(sigc::mem_fun(*this,
	        &TablaComun::fila_activada));

}

TablaComun::~TablaComun() {}

void TablaComun::procesarRespuesta(const Respuesta& rta) {
	_respActual.limpiar();
	_respActual = rta;

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

	this->columns_autosize();
}

void TablaComun::agregarFila(int numFila, const Respuesta& resp) {
	 Gtk::TreeModel::Row filaNueva = *(_refTreeModel->append());

	 for (unsigned i = 0; i < resp.cantidadColumnas() ; i++)
		 filaNueva[_colModelo->_columnas[i]] = resp.dato(numFila, i);
}

void TablaComun::agregarColumnas() {
	for (int i = 0; i < _colModelo->_cantCol ; i++) {
		this->append_column(this->consulta.resultado(i),_colModelo->_columnas[i] );
	}
}
void TablaComun::fila_activada(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {

//	std::cout << "Direccion de COlumna: "<< column << std::endl;
//	std::cout << "Nombre COl: " <<column->get_title() << std::endl;
//	std::cout << "A string de Path: " << path.to_string() << std::endl;

	std::string dimension, valor;

//	for (unsigned i = 0; i < path.size() ; i++) {
//
//		Gtk::TreePath::const_reference referencia = path[i];
//		std::cout << "Referencia al Path " << i <<": " << referencia << std::endl;
//	}

	int col = 0;
	bool colEncontrada = false;
	for (int  i = 0; i < this->_colModelo->_cantCol && !colEncontrada; i++) {
		if (column == this->get_column(i)) {
			colEncontrada = true;
			col = i;
		}
	}

	if (!colEncontrada)
		throw "COLUMAN NO ENCONTRADA PARA NAVEGACION DE TABLA COMUN";

//	std::cout << "TIPO: " << column->get_title() << std::endl;
//	std::cout << "COLUMNA: " << col << std::endl;
//	std::cout << "DATO: " << _respActual.dato(path[0], col) << std::endl;

	dimension = column->get_title();
	valor = _respActual.dato(path[0], col);

	padre->difundirNavegacionSeleccionada(dimension, valor);
}
