#include "TabAdminConfigPassword.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "ArchivoConfiguracion.h"
#include "Utilitario.h"
#include "Definiciones.h"
#include <gtkmm/paned.h>

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

bool TabAdminConfigPassword::aplicarCambios() {
    Glib::ustring passActual = pEntryPassActual->get_text();
    Glib::ustring passNueva = pEntryPassNueva->get_text();

    // si están vacías, no se intentó modificar nada, termina el método
    if (passActual == "" && passNueva == "")
        return true;

    ArchivoConfiguracion arch("servRemoto.conf");
    std::string atr = CLAVE_ATR;
    Glib::ustring pvieja = arch.obtenerAtributo(atr);
    if (pvieja == passActual) {
        std::string pnueva(passNueva);
		arch.setearAtributo(atr,pnueva);
	} else {
		return false;
	}
    return true;
}

void TabAdminConfigPassword::limpiar_pass_entries() {
    pEntryPassActual->set_text("");
    pEntryPassNueva->set_text("");
}
