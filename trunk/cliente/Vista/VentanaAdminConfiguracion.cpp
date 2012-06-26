#include "VentanaAdminConfiguracion.h"
#include <gtkmm/button.h>
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabAdminConfigConexion.h"
#include "TabAdminConfigConsultas.h"

#define VBOX_TAB_CONEXION "vboxTabAdminConfigConexion"
#define VBOX_TAB_CONSULTAS "vboxTabAdminConfigConsultas"
#define BOTON_APLICAR_CONFIG "BotonAplicarConfig"
#define BOTON_CANCELAR_CONFIG "BotonCancelarConfig"

VentanaAdminConfiguracion::VentanaAdminConfiguracion(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Window(cobject), Buildable(_builder) {
    TabAdminConfigConexion* tabConexion;
    get_widget_derived(VBOX_TAB_CONEXION, tabConexion);
    tabs.push_back(tabConexion);

    TabAdminConfigConsultas* tabConsultas;
    get_widget_derived(VBOX_TAB_CONSULTAS, tabConsultas);
    tabs.push_back(tabConsultas);

    Gtk::Button* pBotonAux;

    get_widget(BOTON_APLICAR_CONFIG, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_aplicar_button_clicked));

    get_widget(BOTON_CANCELAR_CONFIG, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaAdminConfiguracion::on_cancelar_button_clicked));
}

VentanaAdminConfiguracion::~VentanaAdminConfiguracion() {}

void VentanaAdminConfiguracion::on_aplicar_button_clicked() {
    std::list< TabAdminConfig* >::iterator it = tabs.begin();
    bool pudoGuardar = true;
    while (pudoGuardar && it != tabs.end())
        pudoGuardar = (*it++)->aplicarCambios();

    if (it == tabs.end())
        hide();
}

void VentanaAdminConfiguracion::on_cancelar_button_clicked() {
    hide();
}
