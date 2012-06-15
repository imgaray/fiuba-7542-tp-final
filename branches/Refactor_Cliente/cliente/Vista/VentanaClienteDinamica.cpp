#include "VentanaClienteDinamica.h"
#include "Tab.h"
#include <iostream>

VentanaClienteDinamica::VentanaClienteDinamica(BaseObjectType* cobject,
                               const Glib::RefPtr< Gtk::Builder >& builder)
    : Gtk::Notebook(cobject) {}

VentanaClienteDinamica::~VentanaClienteDinamica() {}

void VentanaClienteDinamica::personalizar(const char* archivo) {
    if (!dynBuilder.personalizarDesdeArchivo(archivo)) {
        std::cout << "Error al abrir el archivo de personalización " << archivo
                  << ". Contáctese con el administrador." << std::endl;
        return;
    }

    while (dynBuilder.tieneSiguiente()) {
        Tab& t = dynBuilder.siguiente();
        agregarConsultante(&t);
        append_page(t, t.getEtiqueta());
    }
}

void VentanaClienteDinamica::hacerConsulta(ServidorRemoto& server) {
    int pag = get_current_page();
    std::list< PadreDeConsultantes* >::iterator it = hijos.begin();
    for (int i = 0; i < pag; ++i)
        ++it;

    (*it)->hacerConsulta(server);
}
