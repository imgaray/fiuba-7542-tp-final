#include "VentanaAdminConfiguracion.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include <gtkmm/button.h>

#define BOTON_APLICAR_CONFIG "BotonAplicarConfig"
#define BOTON_CANCELAR_CONFIG "BotonCancelarConfig"

VentanaAdminConfiguracion::VentanaAdminConfiguracion(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Window(cobject), builder(_builder) {
    Gtk::Button* pBotonAux;

    builder->get_widget(BOTON_APLICAR_CONFIG, pBotonAux);
    if (pBotonAux)
        pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_aplicar_button_clicked));
    else
        throw ExcepcionArchivoGladeCorrupto(BOTON_APLICAR_CONFIG);


    builder->get_widget(BOTON_CANCELAR_CONFIG, pBotonAux);
    if (pBotonAux)
        pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_cancelar_button_clicked));
    else
        throw ExcepcionArchivoGladeCorrupto(BOTON_CANCELAR_CONFIG);

}

VentanaAdminConfiguracion::~VentanaAdminConfiguracion() {}

void VentanaAdminConfiguracion::on_aplicar_button_clicked() {
    hide();
}

void VentanaAdminConfiguracion::on_cancelar_button_clicked() {
    hide();
}
