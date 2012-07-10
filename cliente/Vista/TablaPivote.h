/*
 * TablaPivote.h
 *
 *  Created on: 23/06/2012
 *      Author: migue
 */

#ifndef TABLAPIVOTE_H_
#define TABLAPIVOTE_H_
#include <gtkmm/liststore.h>
#include "Tabla.h"

/** @class TablaPivote
 * Consultante que muestra sus resultados como una tabla común. Sólo admite
 * hechos en sus resultados.
 */
class TablaPivote : public Tabla {
public:
    /**
     * Constructor.
     * @param filtradores filtradores del panel
     */
	TablaPivote(FiltradoresPanel* filtradores);
    /**
     * Destructor.
     */
	virtual ~TablaPivote();
protected:
	void procesarRespuesta(const Respuesta& resp);

	void agregarFila(int numFila, const Respuesta& resp);
	void agregarColumnas();

	// Puede ser temporal
	Glib::RefPtr<Gtk::ListStore> _refTreeModel;
};

#endif /* TABLAPIVOTE_H_ */
