/*
 * Tabla.h
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#ifndef TABLA_H_
#define TABLA_H_
#include <gtkmm.h>
#include "ExhibidorRespuesta.h"
#include <string>


class Tabla : public ExhibidorRespuesta, public Gtk::TreeView {
public:
	Tabla();
	virtual ~Tabla();

protected:

	virtual void procesarRespuesta(const Respuesta& rta);

	class ColumnasModelo : public Gtk::TreeModel::ColumnRecord {
	public:
		ColumnasModelo(int cantidadColumnas){
			_columnas = NULL;
			if (cantidadColumnas > 0) {
				_cantCol = cantidadColumnas;
				_columnas = new Gtk::TreeModelColumn<std::string>[_cantCol];
			}
			else {
				throw "Cantidad Columnas Insuficiente";
			}
		}

		~ColumnasModelo() {
			if (_columnas != NULL)
				delete[] _columnas;
		}

		Gtk::TreeModelColumn<std::string> *_columnas;
		int _cantCol;
	};

	ColumnasModelo *_colModelo;
};
#endif /* TABLA_H_ */
