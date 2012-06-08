#include "Tab.h"

Tab::Tab(int i, const Glib::ustring& _etiqueta): etiqueta(_etiqueta) {}

Tab::Tab(const std::string& xml) {}

Tab::~Tab() {}

const Glib::ustring& Tab::getEtiqueta() {
    return etiqueta;
}
