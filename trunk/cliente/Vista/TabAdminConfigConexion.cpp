#include "TabAdminConfigConexion.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "ArchivoConfiguracion.h"
#include "Utilitario.h"

#define ENTRY_IP "entryIP"
#define SPIN_BUTTON_PUERTO "spinbuttonPuerto"

TabAdminConfigConexion::TabAdminConfigConexion(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder) {
	get_widget(ENTRY_IP, pEntryIP);

	get_widget(SPIN_BUTTON_PUERTO, pSpinButtonPuerto);

	ArchivoConfiguracion::iterator iter;
	std::string apertura = "servRemoto.conf";
	ArchivoConfiguracion arch(apertura.c_str());

	std::string _ip = "direccion_servidor";
    pEntryIP->set_text(arch.obtenerAtributo(_ip));
    std::string _puerto = "puerto_servidor";
    Utilitario u;
    double a = u.convertirAEntero(arch.obtenerAtributo(_puerto));
    pSpinButtonPuerto->set_value(a);
}

TabAdminConfigConexion::~TabAdminConfigConexion() {}

#include <iostream>
bool TabAdminConfigConexion::aplicarCambios() {
    std::string IP = pEntryIP->get_text();
    std::string puerto = pSpinButtonPuerto->get_text();
    ArchivoConfiguracion arch("servRemoto.conf");
    std::string clave_ip = "direccion_servidor";
    std::string clave_puerto = "puerto_servidor";
    arch.setearAtributo(clave_ip, IP);
    arch.setearAtributo(clave_puerto, puerto);
    return true;
}
