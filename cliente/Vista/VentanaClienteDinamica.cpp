#include "VentanaClienteDinamica.h"
#include "Tab.h"
#include "Consultante.h"
#include "ExcepcionConsultanteNoExiste.h"
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


void VentanaClienteDinamica::agregarConsultanteConcreto(Consultante *cons) {
	if (cons == NULL) {
		throw ExcepcionConsultanteNoExiste("Consultante Nulo en agregarConsultante");
	}

	_mConsultas[cons->getID()] = cons;
}

Consultante* VentanaClienteDinamica::devolverConsultante(Id_Mensaje id) {
	MapaConsultantesNB::iterator it;

	it = _mConsultas.find(id);

	if (it != _mConsultas.end()) {
		return it->second;
	}
	else {
		return NULL;
	}
}
