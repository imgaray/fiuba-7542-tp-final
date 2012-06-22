#include "VentanaCliente.h"
#include <iostream>
#include <cstdlib>
#include <gtkmm/builder.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include "VentanaClienteDinamica.h"
#include "ExcepcionConsultanteNoExiste.h"
#include "Consultante.h"

#define TIMEOUT 10000

#define V_DINAMICA "VentanaDinamica"
#define BOTON_ACTUALIZAR "HerramientaActualizar"
#define BOTON_DETENER_ACTUALIZAR "HerramientaDetenerActualizar"
#define BOTON_EXPORTAR_PDF "HerramientaExportarPDF"
#define BOTON_CONFIGURAR "HerramientaConfigurar"
#define BOTON_SALIR "HerramientaSalir"
#define BOTON_CONECTAR "HerramientaConectar"

VentanaCliente::VentanaCliente(BaseObjectType* cobject,
    const Glib::RefPtr< Gtk::Builder >& _builder)
    : Gtk::Window(cobject), builder(_builder) {
    srand(time(NULL));
    Gtk::ToolButton* pAux;

    builder->get_widget_derived(V_DINAMICA, pVDinamica);
    if (!pVDinamica) {
        std::cout << "Se rompió algo" << std::endl;
        return;
    }

    builder->get_widget(BOTON_CONECTAR, pAux);
    if (pAux) {
        botones[BOTON_CONECTAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_conectar_button_clicked));
    }

    builder->get_widget(BOTON_ACTUALIZAR, pAux);
    if (pAux) {
        botones[BOTON_ACTUALIZAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_actualizar_button_clicked));
    }

    builder->get_widget(BOTON_DETENER_ACTUALIZAR, pAux);
    if (pAux) {
        botones[BOTON_DETENER_ACTUALIZAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_detenerActualizar_button_clicked));
    }

    builder->get_widget(BOTON_EXPORTAR_PDF, pAux);
    if (pAux) {
        botones[BOTON_EXPORTAR_PDF] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_exportarPDF_button_clicked));
    }

    builder->get_widget(BOTON_CONFIGURAR, pAux);
    if (pAux) {
        botones[BOTON_CONFIGURAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_configurar_button_clicked));
    }

    builder->get_widget(BOTON_SALIR, pAux);
    if (pAux) {
        botones[BOTON_SALIR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_salir_button_clicked));
    }
terminoConLosFiltros = false;
}

VentanaCliente::~VentanaCliente() {}

void VentanaCliente::personalizar(const char* archivo) {
    pVDinamica->personalizar(archivo);
}

void VentanaCliente::on_conectar_button_clicked() {
    std::cout << BOTON_CONECTAR " clicked." << std::endl;
    try {
        server.conectar();
        pVDinamica->hacerConsultaFiltros(server);
        botones[BOTON_ACTUALIZAR]->set_sensitive();
        botones[BOTON_DETENER_ACTUALIZAR]->set_sensitive();
        botones[BOTON_EXPORTAR_PDF]->set_sensitive();
        botones[BOTON_CONECTAR]->set_sensitive(false);

        Glib::signal_timeout().connect(sigc::mem_fun(*this,
                    &VentanaCliente::on_timeout), TIMEOUT);
        Glib::signal_idle().connect(sigc::mem_fun(*this,
                    &VentanaCliente::on_idle));
    }
    catch (const char* msj) {
        Gtk::MessageDialog dialog(*this,
                                  msj,
                                  false,
                                  Gtk::MESSAGE_ERROR,
                                  Gtk::BUTTONS_OK,
                                  true);
        dialog.run();
    }
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

bool VentanaCliente::on_idle() {
//    std::cout << "Inactivo... yendo a buscar respuestas..." << std::endl;
    if (!terminoConLosFiltros)
        terminoConLosFiltros = pVDinamica->retirarRespuestasFiltros(server);
    else
        pVDinamica->retirarRespuestas(server);

    return true;
}
