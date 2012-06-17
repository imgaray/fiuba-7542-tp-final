#include "Tab.h"
#include <iostream>

Tab::Tab(int i, const Glib::ustring& _etiqueta): etiqueta(_etiqueta) {
    etiquetaCompuesta.pack_end(etiqueta, false, false);
    etiquetaCompuesta.pack_end(s, false, false);
    etiqueta.show();
    s.hide();
}

Tab::Tab(const std::string& xml) {}

Tab::~Tab() {}

Gtk::HBox& Tab::getEtiqueta() {
    return etiquetaCompuesta;
}
