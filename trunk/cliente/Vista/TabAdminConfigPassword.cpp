#include "TabAdminConfigPassword.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "ArchivoConfiguracion.h"
#include "Utilitario.h"

#define ENTRY_PASS_ACTUAL "entryPassActual"
#define ENTRY_PASS_NUEVA "entryPassNueva"

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
    // encriptar y persistir!
    return true;
}
