/*
 * TablaComun.h
 *
 *  Created on: 22/06/2012
 *      Author: migue
 */

#ifndef TABLACOMUN_H_
#define TABLACOMUN_H_

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

	Glib::RefPtr<Gtk::ListStore> _refTreeModel;
};

#endif /* TABLACOMUN_H_ */
