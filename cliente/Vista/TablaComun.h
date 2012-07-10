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
	TablaComun(FiltradoresPanel* filtradores);
	virtual ~TablaComun();

protected:
	virtual void procesarRespuesta(const Respuesta& rta);

	void agregarFila(int numFila, const Respuesta& resp);
	void agregarColumnas();


    /**
     * @brief Signal handler para el doble click sobre alguna celda.
     * @param path camino hacia la fila activada
     * @param column columna de la fila activada
     *
     * Busca el par de valores < nombre_columna, valor_celda > e
     * inicializa la cascada de llamadas
     * (void Tab::difundirNavegacionSeleccionada(const Glib::ustring& ,
     * const Glib::ustring& )) para que se interprete la navegación.
     */
	void fila_activada(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* column);

	Glib::RefPtr<Gtk::ListStore> _refTreeModel;

	Respuesta _respActual;
};

#endif /* TABLACOMUN_H_ */
