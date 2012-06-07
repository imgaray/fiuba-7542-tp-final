#include "Tab.h"

Tab::Tab(int x, int y, bool homog, const Glib::ustring& _etiqueta)
: Gtk::Table(x, y, homog), etiqueta(_etiqueta) {}

Tab::Tab(const std::string& xml) {}

Tab::~Tab() {}

const Glib::ustring& Tab::getEtiqueta() {
    return etiqueta;
}
