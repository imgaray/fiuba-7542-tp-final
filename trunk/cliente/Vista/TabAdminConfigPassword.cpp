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
	pEntryPassActual->signal_changed().connect(sigc::mem_fun(*this,
		&TabAdminConfigPassword::on_entry_pass_actual_changed));

	get_widget(ENTRY_PASS_NUEVA, pEntryPassNueva);
	pEntryPassNueva->signal_changed().connect(sigc::mem_fun(*this,
		&TabAdminConfigPassword::on_entry_pass_nueva_changed));
}

TabAdminConfigPassword::~TabAdminConfigPassword() {}

#include <iostream>
bool TabAdminConfigPassword::aplicarCambios() {
    std::cout << "bool TabAdminConfigPassword::aplicarCambios()... (@todo)" << std::endl;
    return true;
}

void TabAdminConfigPassword::on_entry_pass_actual_changed() {
    std::cout << "void TabAdminConfigPassword::on_entry_pass_actual_changed()... cambio registrado."
              << "Si a nadie le importa registrar cada cambio que hace el usuario acá, desconectamos la señal. (@todo)" << std::endl;
    // acá podría registrar lo que ingresó el usuario en una string, con el método pEntryPassActual->get_text()
}

void TabAdminConfigPassword::on_entry_pass_nueva_changed() {
    std::cout << "void TabAdminConfigPassword::on_entry_pass_nueva_changed()... cambio registrado. "
              << "Si a nadie le importa registrar cada cambio que hace el usuario acá, desconectamos la señal. (@todo)" << std::endl;
    // acá podría registrar lo que ingresó el usuario en una string, con el método pEntryPassNueva->get_text()
}
