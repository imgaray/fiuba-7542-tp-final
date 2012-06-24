/*
 * TablaComun.h
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#ifndef TABLACOMUN_H_
#define TABLACOMUN_H_

#include <gtkmm/liststore.h>
#include "Tabla.h"
#include "Respuesta.h"

class TablaComun : public Tabla {
public:
	TablaComun(FiltradoresPanel& filtradores);
	virtual ~TablaComun();

protected:
	virtual void procesarRespuesta(const Respuesta& rta);

	void agregarFila(int numFila, const Respuesta& resp);
	void agregarColumnas();

	void fila_activada(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

	Glib::RefPtr<Gtk::ListStore> _refTreeModel;
};

#endif /* TABLACOMUN_H_ */
