/*
 * Tabla.h
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#ifndef TABLA_H_
#define TABLA_H_
#include <gtkmm/treeview.h>
#include <string>
#include "Consultante.h"

/** @class Tabla
 * Clase abstracta que comprende comportamiento común a un consultante que
 * muestra sus resultados en forma de tabla.
 */
class Tabla : public Consultante, public Gtk::TreeView {
public:
	Tabla(FiltradoresPanel* filtradores);
	virtual ~Tabla();

protected:

    /** @class ColumnasModelo
     * Modelo detrás de la Tabla.
     */
	class ColumnasModelo : public Gtk::TreeModelColumnRecord {
	public:
		ColumnasModelo(int cantidadColumnas){
			_columnas = NULL;
			if (cantidadColumnas > 0) {
				_cantCol = cantidadColumnas;
				_columnas = new Gtk::TreeModelColumn<std::string>[_cantCol];

				for (int i = 0 ; i < _cantCol ; i++) {
					this->add(_columnas[i]);
				}
			}
			else {
				throw "Cantidad Columnas Insuficiente";
			}
		}

		virtual ~ColumnasModelo() {
			if (_columnas != NULL)
				delete[] _columnas;
		}

		Gtk::TreeModelColumn<std::string> *_columnas;
		int _cantCol;
	};

	ColumnasModelo *_colModelo;
	Gtk::Spinner s;
};
#endif /* TABLA_H_ */
