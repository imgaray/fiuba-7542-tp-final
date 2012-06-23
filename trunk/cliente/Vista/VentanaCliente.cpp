#include "VentanaCliente.h"
#include <iostream>
#include <cstdlib>
#include <gtkmm/builder.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include "VentanaClienteDinamica.h"
#include "DialogoAutentif.h"
#include "VentanaAdminConfiguracion.h"
#include "ExcepcionConsultanteNoExiste.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "Consultante.h"

#define TIMEOUT 10000

#define V_DINAMICA "VentanaDinamica"
#define AUTENTIF_ADMIN "AutentificacionAdmin"
#define CONFIG_ADMIN "ConfiguracionAdmin"
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

    builder->get_widget_derived(V_DINAMICA, pVDinamica);
    if (!pVDinamica)
        throw ExcepcionArchivoGladeCorrupto(V_DINAMICA);

    builder->get_widget_derived(AUTENTIF_ADMIN, pDAutentifAdmin);
    if (!pDAutentifAdmin)
        throw ExcepcionArchivoGladeCorrupto(AUTENTIF_ADMIN);

    builder->get_widget_derived(CONFIG_ADMIN, pVAdminConfig);
    if (!pVAdminConfig)
        throw ExcepcionArchivoGladeCorrupto(CONFIG_ADMIN);


    pVDinamica->signal_switch_page().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_page_switched));
    pVDinamica->signal_actualizacion().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_actualizacion_solicitada));

    Gtk::ToolButton* pAux;
    builder->get_widget(BOTON_CONECTAR, pAux);
    if (pAux) {
        botones[BOTON_CONECTAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_conectar_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_CONECTAR);

    builder->get_widget(BOTON_ACTUALIZAR, pAux);
    if (pAux) {
        botones[BOTON_ACTUALIZAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_actualizar_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_ACTUALIZAR);

    builder->get_widget(BOTON_DETENER_ACTUALIZAR, pAux);
    if (pAux) {
        botones[BOTON_DETENER_ACTUALIZAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_detenerActualizar_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_DETENER_ACTUALIZAR);

    builder->get_widget(BOTON_EXPORTAR_PDF, pAux);
    if (pAux) {
        botones[BOTON_EXPORTAR_PDF] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_exportarPDF_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_EXPORTAR_PDF);

    builder->get_widget(BOTON_CONFIGURAR, pAux);
    if (pAux) {
        botones[BOTON_CONFIGURAR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_configurar_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_CONFIGURAR);

    builder->get_widget(BOTON_SALIR, pAux);
    if (pAux) {
        botones[BOTON_SALIR] = pAux;
        pAux->signal_clicked().connect(sigc::mem_fun(*this,
            &VentanaCliente::on_salir_button_clicked));
    } else
        throw ExcepcionArchivoGladeCorrupto(BOTON_SALIR);
}

VentanaCliente::~VentanaCliente() {}

void VentanaCliente::personalizar(const char* archivo) {
    pVDinamica->personalizar(archivo);
}

void VentanaCliente::on_page_switched(GtkNotebookPage* page, guint page_num) {
    std::cout << "Notebook page switched" << std::endl;
    if (server.conectado()) {
        bool actualizable = pVDinamica->disponibleParaActualizacion(page_num);

        botones[BOTON_ACTUALIZAR]->set_sensitive(actualizable);
        botones[BOTON_DETENER_ACTUALIZAR]->set_sensitive(actualizable);
    }
}

void VentanaCliente::on_actualizacion_solicitada(Consultante* c) {
    if (server.conectado())
        c->hacerConsulta(server);
}

void VentanaCliente::on_conectar_button_clicked() {
    std::cout << BOTON_CONECTAR " clicked." << std::endl;
    try {
        server.conectar();
        pVDinamica->hacerConsultaInicial(server);
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
        dialog.set_title("Error al conectar");
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
    std::cout << BOTON_EXPORTAR_PDF " clicked. (@todo)" << std::endl;
}

void VentanaCliente::on_configurar_button_clicked() {
    std::cout << BOTON_CONFIGURAR " clicked." << std::endl;
    if (pDAutentifAdmin->run() == Gtk::RESPONSE_OK) {
        pDAutentifAdmin->hide();
        pVAdminConfig->show();
    } else
        pDAutentifAdmin->hide();
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
    pVDinamica->retirarRespuestas(server);

    return true;
}
