#include "TabAdminConfigConexion.h"
#include "ExcepcionArchivoGladeCorrupto.h"

#define ENTRY_IP "entryIP"
#define SPIN_BUTTON_PUERTO "spinbuttonPuerto"

TabAdminConfigConexion::TabAdminConfigConexion(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder) {
    builder->get_widget(ENTRY_IP, pEntryIP);
    if (pEntryIP)
        pEntryIP->signal_changed().connect(sigc::mem_fun(*this,
            &TabAdminConfigConexion::on_entry_ip_changed));
    else
        throw ExcepcionArchivoGladeCorrupto(ENTRY_IP);

    builder->get_widget(SPIN_BUTTON_PUERTO, pSpinButtonPuerto);
    if (!pSpinButtonPuerto)
        throw ExcepcionArchivoGladeCorrupto(SPIN_BUTTON_PUERTO);
}

TabAdminConfigConexion::~TabAdminConfigConexion() {}

#include <iostream>
bool TabAdminConfigConexion::aplicarCambios() {
    std::cout << "bool TabAdminConfigConexion::aplicarCambios()... guardando en archivo (@todo)" << std::endl;
    return true;
}

void TabAdminConfigConexion::on_entry_ip_changed() {
    std::cout << "void TabAdminConfigConexion::on_entry_ip_changed()... validando IP (@todo)" << std::endl;
}
