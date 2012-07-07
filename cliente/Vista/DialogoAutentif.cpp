#include "DialogoAutentif.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include <gtkmm/button.h>
#include "ArchivoConfiguracion.h"
#include "Cifrador.hpp"
#include <iostream>
#include "Definiciones.h"

#define BOTON_ACEPTAR "BotonAceptar"
#define BOTON_CANCELAR "BotonCancelarAutentif"
#define ENTRY_PASSWORD "PasswordEntry"

DialogoAutentif::DialogoAutentif(BaseObjectType* cobject,
            const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Dialog(cobject), Buildable(_builder) {

    get_widget(ENTRY_PASSWORD, pEntryPassword);

    Gtk::Button* pBotonAux;

    get_widget(BOTON_ACEPTAR, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &DialogoAutentif::on_aceptar_button_clicked));

    get_widget(BOTON_CANCELAR, pBotonAux);
    pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
            &DialogoAutentif::on_cancelar_button_clicked));

//    builder->get_widget(ENTRY_PASSWORD, pEntryPassword);
//    if (!pEntryPassword)
//        throw ExcepcionArchivoGladeCorrupto(ENTRY_PASSWORD);
//
//    Gtk::Button* pBotonAux;
//
//    builder->get_widget(BOTON_ACEPTAR, pBotonAux);
//    if (pBotonAux)
//        pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
//            &DialogoAutentif::on_aceptar_button_clicked));
//    else
//        throw ExcepcionArchivoGladeCorrupto(BOTON_ACEPTAR);
//
//
//    builder->get_widget(BOTON_CANCELAR, pBotonAux);
//    if (pBotonAux)
//        pBotonAux->signal_clicked().connect(sigc::mem_fun(*this,
//            &DialogoAutentif::on_cancelar_button_clicked));
//    else
//        throw ExcepcionArchivoGladeCorrupto(BOTON_CANCELAR);

}

DialogoAutentif::~DialogoAutentif() {}

void DialogoAutentif::on_aceptar_button_clicked() {
	ArchivoConfiguracion arch("servRemoto.conf");
	std::string atr = CLAVE_ATR;
	std::string clave = arch.obtenerAtributo(atr);
	Glib::ustring uclave = pEntryPassword->get_text();
	std::string usrclave = uclave.c_str();
	 if (usrclave == clave) {
        response(Gtk::RESPONSE_OK);
		//std::cout << "DialogoAutentif::on_aceptar_button_clicked(): Tire RESPONSE_OK" << std::endl;
    }else
        response(Gtk::RESPONSE_CANCEL);
}

void DialogoAutentif::on_cancelar_button_clicked() {
    response(Gtk::RESPONSE_CANCEL);
}
