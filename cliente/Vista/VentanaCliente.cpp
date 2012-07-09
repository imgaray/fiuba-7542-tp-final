#include "VentanaCliente.h"
#include <iostream>
#include <gtkmm/builder.h>
#include <gtkmm/main.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/imagemenuitem.h>
#include "VentanaClienteDinamica.h"
#include "DialogoAutentif.h"
#include "VentanaAdminConfiguracion.h"
#include "ExcepcionConsultanteNoExiste.h"
#include "Consultante.h"

#define TIMEOUT_RETIRAR_RESPUESTAS 100

// ventanas
#define V_DINAMICA "VentanaDinamica"
#define AUTENTIF_ADMIN "AutentificacionAdmin"
#define CONFIG_ADMIN "ConfiguracionAdmin"
#define ACERCA_DE "aboutdialog"

// botones
#define BOTON_ACTUALIZAR "HerramientaActualizar"
#define BOTON_DETENER_ACTUALIZAR "HerramientaDetenerActualizar"
#define BOTON_CONFIGURAR "HerramientaConfigurar"
#define BOTON_SALIR "HerramientaSalir"
#define BOTON_CONECTAR "HerramientaConectar"

// menú
#define MENU_SALIR "menuSalir"
#define MENU_CONFIGURAR "menuConfigurar"
#define MENU_ACERCA_DE "menuAcercaDe"

VentanaCliente::VentanaCliente(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Window(cobject), Buildable(_builder) {
    initVentanas();
    initBotones();
    initBarraDeMenu();
}

VentanaCliente::~VentanaCliente() {
    delete pDAutentifAdmin;
    delete pVAdminConfig;
    delete pDAbout;
}

void VentanaCliente::initVentanas() {
    get_widget_derived(V_DINAMICA, pVDinamica);
    get_widget_derived(AUTENTIF_ADMIN, pDAutentifAdmin);
    get_widget_derived(CONFIG_ADMIN, pVAdminConfig);
    get_widget(ACERCA_DE, pDAbout);

    pVDinamica->signal_actualizacion().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_actualizacion_solicitada));
}

void VentanaCliente::initBotones() {
    Gtk::ToolButton* pAux;

    get_widget(BOTON_CONECTAR, pAux);
    botones[BOTON_CONECTAR] = pAux;
    pAux->signal_clicked().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_conectar_button_clicked));

    get_widget(BOTON_ACTUALIZAR, pAux);
    botones[BOTON_ACTUALIZAR] = pAux;
    pAux->signal_clicked().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_actualizar_button_clicked));

    get_widget(BOTON_DETENER_ACTUALIZAR, pAux);
    botones[BOTON_DETENER_ACTUALIZAR] = pAux;
    pAux->signal_clicked().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_detenerActualizar_button_clicked));

    get_widget(BOTON_CONFIGURAR, pAux);
    botones[BOTON_CONFIGURAR] = pAux;
    pAux->signal_clicked().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_configurar_button_clicked));

    get_widget(BOTON_SALIR, pAux);
    botones[BOTON_SALIR] = pAux;
    pAux->signal_clicked().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_salir_button_clicked));
}

void VentanaCliente::initBarraDeMenu() {
    Gtk::ImageMenuItem* pAux;

    get_widget(MENU_SALIR, pAux);
    pAux->signal_activate().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_salir_button_clicked));

    get_widget(MENU_CONFIGURAR, pAux);
    pAux->signal_activate().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_configurar_button_clicked));

    get_widget(MENU_ACERCA_DE, pAux);
    pAux->signal_activate().connect(sigc::mem_fun(*this,
        &VentanaCliente::on_acerca_de_button_clicked));
}

void VentanaCliente::personalizar(const char* archivo) {
    pVAdminConfig->setVDinamica(pVDinamica);
    pVAdminConfig->setArchivoPersonalizador(archivo);
}

void VentanaCliente::on_actualizacion_solicitada(Consultante* c) {
    if (server.conectado())
        c->hacerConsulta(server);
}

void VentanaCliente::on_conectar_button_clicked() {
    try {
        server.conectar();
        pVDinamica->hacerConsultaInicial(server);
        botones[BOTON_CONECTAR]->set_sensitive(false);
        botones[BOTON_ACTUALIZAR]->set_sensitive(true);
        botones[BOTON_DETENER_ACTUALIZAR]->set_sensitive(true);

        Glib::signal_timeout().connect(sigc::mem_fun(*this,
                    &VentanaCliente::on_timeout), TIMEOUT_RETIRAR_RESPUESTAS);
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
    pVDinamica->hacerConsulta(server);
}

void VentanaCliente::on_detenerActualizar_button_clicked() {
    pVDinamica->cancelarConsulta(server);
}

void VentanaCliente::on_configurar_button_clicked() {
    if (pDAutentifAdmin->run() == Gtk::RESPONSE_OK) {
        pDAutentifAdmin->hide();
        pVAdminConfig->show();
    } else
        pDAutentifAdmin->hide();
}

void VentanaCliente::on_salir_button_clicked() {
    hide();
}

void VentanaCliente::on_acerca_de_button_clicked() {
    pDAbout->run();
}

bool VentanaCliente::on_timeout() {
    pVDinamica->retirarRespuestas(server);
    return true;
}
