#include "VentanaCliente.h"
#include <iostream>
#include <cstdlib>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/notebook.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/main.h>
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Hecho.h"
#include "Tab.h"

#define NOTEBOOK "Notebook"
#define BOTON_ACTUALIZAR "HerramientaActualizar"
#define BOTON_DETENER_ACTUALIZAR "HerramientaDetenerActualizar"
#define BOTON_EXPORTAR_PDF "HerramientaExportarPDF"
#define BOTON_CONFIGURAR "HerramientaConfigurar"
#define BOTON_SALIR "HerramientaSalir"

VentanaCliente::VentanaCliente(BaseObjectType* cobject,
    const Glib::RefPtr<Gtk::Builder>& _builder)
    : Gtk::Window(cobject), builder(_builder) {
    srand(time(NULL));
    Gtk::ToolButton* pAux;

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
}

VentanaCliente::~VentanaCliente() {}

void VentanaCliente::personalizar(const char* archivo) {
    if (!dynBuilder.personalizarDesdeArchivo(archivo)) {
        std::cout << "Error al abrir el archivo de personalización " << archivo
                  << ". Contáctese con el administrador." << std::endl;
        return;
    }

    Gtk::Notebook* pNotebook;
    builder->get_widget(NOTEBOOK, pNotebook);
    if (pNotebook)
        while (dynBuilder.tieneSiguiente()) {
            Tab& t = dynBuilder.siguiente();
            pNotebook->append_page(t, t.getEtiqueta());
        }
}

void VentanaCliente::on_actualizar_button_clicked() {
    std::cout << BOTON_ACTUALIZAR " clicked." << std::endl;
    unsigned tt = rand() % 8 + 1;
    double valor;
    Glib::ustring nombres[9] = { "Migue", "Nacho", "Maria", "Micaela",
        "Sebastian", "Sandra", "Pablo", "Gonzalo", "Julia" };
    std::list< Hecho > datos;
    for (unsigned i = 0; i < tt; ++i) {
        valor = (rand() % 100 + 1) * 1.123456789;
        datos.push_back(Hecho(nombres[i] , valor));
    }

    gBarras.actualizarDatos(datos);
    gTorta.actualizarDatos(datos);

    Gtk::Notebook* pNotebook;
    builder->get_widget(NOTEBOOK, pNotebook);
    if (pNotebook)
        pNotebook->queue_draw();
}

void VentanaCliente::on_detenerActualizar_button_clicked() {
    std::cout << BOTON_DETENER_ACTUALIZAR " clicked." << std::endl;
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
