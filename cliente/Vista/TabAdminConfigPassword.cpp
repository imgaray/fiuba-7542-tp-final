#include "TabAdminConfigPassword.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "ArchivoConfiguracion.h"
#include "Utilitario.h"
#include "Definiciones.h"

#define ENTRY_PASS_ACTUAL "entryPassActual"
#define ENTRY_PASS_NUEVA "entryPassNueva"

#define PASS 115


TabAdminConfigPassword::TabAdminConfigPassword(BaseObjectType* cobject,
                                const Glib::RefPtr< Gtk::Builder >& _builder)
: TabAdminConfig(cobject, _builder) {
	get_widget(ENTRY_PASS_ACTUAL, pEntryPassActual);
	get_widget(ENTRY_PASS_NUEVA, pEntryPassNueva);
}

TabAdminConfigPassword::~TabAdminConfigPassword() {}

#include <iostream>
bool TabAdminConfigPassword::aplicarCambios() {
    std::cout << "bool TabAdminConfigPassword::aplicarCambios()... (@todo)" << std::endl;
    Glib::ustring passActual = pEntryPassActual->get_text();
    Glib::ustring passNueva = pEntryPassNueva->get_text();
    std::string pactual = passActual.c_str();
    std::string pnueva = passNueva.c_str();
    ArchivoConfiguracion arch("servRemoto.conf");
    std::string atr = CLAVE_ATR;
    std::string pvieja = arch.obtenerAtributo(atr);
    if (pvieja == pactual) {
		arch.setearAtributo(atr,pnueva);
	} else {
		return false;
	}
    return true;
}
