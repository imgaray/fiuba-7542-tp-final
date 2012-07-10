/*
 * Cliente.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Cliente.h"
#include <gtkmm/main.h>
#include "VentanaCliente.h"
#include "ExcepcionArchivoGladeCorrupto.h"

#define UI_ESTATICA "Cliente UI.glade"
#define UI_DINAMICA "ventanaPersonalizada.xml"
#define VENTANA_CLIENTE "VentanaCliente"

Cliente::Cliente(int argc, char* argv[]) {
    pVentana = NULL;
    initGtk(argc, argv);
}

Cliente::~Cliente() {
	delete pVentana;
}

void Cliente::run() {
    Gtk::Main::run(*pVentana);
}

void Cliente::initGtk(int argc, char* argv[]) {
    Glib::RefPtr< Gtk::Builder > builder = Gtk::Builder::create();

    builder->add_from_file(UI_ESTATICA);

    builder->get_widget_derived(VENTANA_CLIENTE, pVentana);
    if (pVentana) {
        pVentana->personalizar(UI_DINAMICA);
        pVentana->show_all();
    } else
        throw ExcepcionArchivoGladeCorrupto(VENTANA_CLIENTE);
}
