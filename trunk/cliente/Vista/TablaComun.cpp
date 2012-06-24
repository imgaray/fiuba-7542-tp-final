/*
 * TablaComun.cpp
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#include "TablaComun.h"
#include <iostream>
#include <string>

void mensaje(const std::string& msj) {
	std::cout << "++++++++++++++++++++++++CLIENTE: " << msj << std::endl;
}

using std::cout;
using std::endl;
using std::string;

void __imprimirRespuesta(const Respuesta& resp, const string& comentario) {
	cout << endl;
	cout << "Comentario: " << comentario << endl;
	cout << "Estado Resp: " << resp.mensajeInterno() << endl;
	cout << "Cantidad Filas: " << resp.cantidadFilas() << endl;
	cout << "Cantidad Columnas: " << resp.cantidadColumnas() << endl;
	cout << "Datos Recibidos:" << endl;
	for (unsigned i = 0; i < resp.cantidadFilas() ; i++)  {
		cout << "::";
		for (unsigned j = 0 ; j < resp.cantidadColumnas() ; j++) {
			cout.width(14);
			cout.fill('.');
			cout<< resp.dato(i,j) << "|";
		}
		cout << endl;
	}
}


TablaComun::TablaComun(FiltradoresPanel& filtradores) : Tabla(filtradores) {

	this->signal_row_activated().connect(sigc::mem_fun(*this,
	        &TablaComun::fila_activada));
}

TablaComun::~TablaComun() {
	mensaje("Se Destruye la Tabla Comun");
}

void TablaComun::procesarRespuesta(const Respuesta& rta) {
	mensaje("Se entro a procesar la Respuesta");

	__imprimirRespuesta(rta, "Respuesta De TablaComun");

	if (_colModelo != NULL) {
		this->remove_all_columns();
		delete _colModelo;
		//_refTreeModel.clear();
	}

	_colModelo = new ColumnasModelo(rta.cantidadColumnas());

	 _refTreeModel = Gtk::ListStore::create(*_colModelo);
	 this->set_model(_refTreeModel);

	 for (int i = 0; i < rta.cantidadFilas() ; i++) {
		 agregarFila(i, rta);
	 }

	agregarColumnas();

	mensaje("Se termino el procesarRespuesta");
}

void TablaComun::agregarFila(int numFila, const Respuesta& resp) {
	 Gtk::TreeModel::Row filaNueva = *(_refTreeModel->append());

	 for (unsigned i = 0; i < resp.cantidadColumnas() ; i++) {
		 filaNueva[_colModelo->_columnas[i]] = resp.dato(numFila, i);
		 mensaje("Se agrego el dato: " + resp.dato(numFila, i));
	 }
}

void TablaComun::agregarColumnas() {
	for (int i = 0; i < _colModelo->_cantCol ; i++) {
		this->append_column(this->consulta.resultado(i),_colModelo->_columnas[i] );
	}
}
void TablaComun::fila_activada(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column) {
	std::cout << "/////////////////////////////SE ACTIVO UNA FILA//////////////////" << std::endl;
}
