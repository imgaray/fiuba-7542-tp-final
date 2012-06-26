#include "DialogoAutentif.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include <gtkmm/button.h>

#define BOTON_ACEPTAR "BotonAceptar"
#define BOTON_CANCELAR "BotonCancelarAutentif"
#define ENTRY_PASSWORD "PasswordEntry"

#define ADMIN_PASSWORD "7542"

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
    if (pEntryPassword->get_text() == ADMIN_PASSWORD)
        response(Gtk::RESPONSE_OK);
    else
        response(Gtk::RESPONSE_CANCEL);
}

void DialogoAutentif::on_cancelar_button_clicked() {
    response(Gtk::RESPONSE_CANCEL);
}
