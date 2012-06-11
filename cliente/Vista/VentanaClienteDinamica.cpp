#include "VentanaClienteDinamica.h"
#include "Tab.h"
#include <iostream>

VentanaClienteDinamica::VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder)
    : Gtk::Notebook(cobject) {

}

VentanaClienteDinamica::~VentanaClienteDinamica() {}

void VentanaClienteDinamica::personalizar(const char* archivo) {
    if (!dynBuilder.personalizarDesdeArchivo(archivo)) {
        std::cout << "Error al abrir el archivo de personalización " << archivo
                  << ". Contáctese con el administrador." << std::endl;
        return;
    }

    while (dynBuilder.tieneSiguiente()) {
        Tab& t = dynBuilder.siguiente();
        std::cout << "Pvcd agregó un hijo (tab: " << &t << ")" << std::endl;
        agregarConsultante(&t);
        append_page(t, t.getEtiqueta());
    }
}
