#include "VentanaCliente.h"
#include <iostream>
#include <cstdlib>
#include <gtkmm/builder.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/main.h>
#include "VentanaClienteDinamica.h"

#define TIMEOUT 10000

#define NOTEBOOK "Notebook"
#define BOTON_ACTUALIZAR "HerramientaActualizar"
#define BOTON_DETENER_ACTUALIZAR "HerramientaDetenerActualizar"
#define BOTON_EXPORTAR_PDF "HerramientaExportarPDF"
#define BOTON_CONFIGURAR "HerramientaConfigurar"
#define BOTON_SALIR "HerramientaSalir"

VentanaCliente::VentanaCliente(BaseObjectType* cobject,
    const Glib::RefPtr< Gtk::Builder >& _builder)
    : Gtk::Window(cobject), builder(_builder) {
    srand(time(NULL));
    Gtk::ToolButton* pAux;

    builder->get_widget_derived(NOTEBOOK, pVDinamica);
    if (!pVDinamica) {
        std::cout << "Se rompió algo" << std::endl;
        return;
    }

    builder->get_widget(BOTON_ACTUALIZAR, pAux);
    if (pAux)
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_actualizar_button_clicked));

    builder->get_widget(BOTON_DETENER_ACTUALIZAR, pAux);
    if (pAux)
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_detenerActualizar_button_clicked));

    builder->get_widget(BOTON_EXPORTAR_PDF, pAux);
    if (pAux)
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_exportarPDF_button_clicked));

    builder->get_widget(BOTON_CONFIGURAR, pAux);
    if (pAux)
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_configurar_button_clicked));

    builder->get_widget(BOTON_SALIR, pAux);
    if (pAux)
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_salir_button_clicked));

    Glib::signal_timeout().connect(sigc::mem_fun(*this,
                                    &VentanaCliente::on_timeout), TIMEOUT);
}

VentanaCliente::~VentanaCliente() {}

void VentanaCliente::personalizar(const char* archivo) {
    pVDinamica->personalizar(archivo);
}

void VentanaCliente::on_actualizar_button_clicked() {
    std::cout << BOTON_ACTUALIZAR " clicked." << std::endl;

    pVDinamica->hacerConsulta(server);
}

void VentanaCliente::on_detenerActualizar_button_clicked() {
    std::cout << BOTON_DETENER_ACTUALIZAR " clicked." << std::endl;

    pVDinamica->cancelarConsulta(server);
}

void VentanaCliente::on_exportarPDF_button_clicked() {
    std::cout << BOTON_EXPORTAR_PDF " clicked." << std::endl;
}

void VentanaCliente::on_configurar_button_clicked() {
    std::cout << BOTON_CONFIGURAR " clicked." << std::endl;
}

void VentanaCliente::on_salir_button_clicked() {
    hide();
}

bool VentanaCliente::on_timeout() {
//    pVDinamica->hacerConsulta(server);
    return true;
}
