/*
 * Cliente.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Cliente.h"
#include <iostream>
#include <gtkmm/main.h>
#include "VentanaCliente.h"

#define UI_ESTATICA "Vista/Cliente UI.glade"
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
    if (pVentana)
        Gtk::Main::run(*pVentana);
    else
        std::cerr << "Gtk::Builder::get_derived_widget(...) error"
                  << std::endl;
}

void Cliente::initGtk(int argc, char* argv[]) {
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    try {
        builder->add_from_file(UI_ESTATICA);
    }
    catch(const Glib::FileError& e) {
        std::cerr << "FileError: " << e.what() << std::endl;
        return;
    }
    catch(const Gtk::BuilderError& e) {
        std::cerr << "BuilderError: " << e.what() << std::endl;
        return;
    }
    catch(const Glib::MarkupError& e) {
        std::cerr << "MarkupError: " << e.what() << std::endl;
        return;
    }

    builder->get_widget_derived(VENTANA_CLIENTE, pVentana);
    if (pVentana) {
        pVentana->personalizar(UI_DINAMICA);
        pVentana->show_all();
    }
}
