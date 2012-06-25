/*
 * Tabla.h
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#ifndef TABLA_H_
#define TABLA_H_
#include <gtkmm/treeview.h>
#include "ExhibidorRespuesta.h"
#include <string>


class Tabla : public ExhibidorRespuesta, public Gtk::TreeView {
public:
	Tabla(FiltradoresPanel& filtradores);
	virtual void actualizarTamanioMinimo(double x, double y) {
		// @todo Completar este metodo SEBAAAAAAAAAA!!!!!!
	}

	virtual ~Tabla();

protected:
	//virtual void procesarRespuesta(const Respuesta& rta) = 0;

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
};
#endif /* TABLA_H_ */
