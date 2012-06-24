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
	/*
	mensaje("Se crea la Tabla Comun");

	Respuesta respEj;
	respEj.definirColumnas(3);

	this->consulta.agregarResultado("COLumna 1");
	this->consulta.agregarResultado("COLumna 2");
	this->consulta.agregarResultado("COLumna 3");

	respEj.agregar("Col 1-1");
	respEj.agregar("Col 2-1");
	respEj.agregar("Col 3-1");
	respEj.filaCompletada();

	respEj.agregar("Col 1-2");
	respEj.agregar("Col 2-2");
	respEj.agregar("Col 3-2");
	respEj.filaCompletada();

	respEj.agregar("Col 1-3");
	respEj.agregar("Col 2-3");
	respEj.agregar("Col 3-3");
	respEj.filaCompletada();

	respEj.agregar("Col 1-4");
	respEj.agregar("Col 2-4");
	respEj.agregar("Col 3-4");
	respEj.filaCompletada();

	procesarRespuesta(respEj);
	*/
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
