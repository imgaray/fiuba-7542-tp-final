#ifndef DIALOGO_AUTENTIF_H
#define DIALOGO_AUTENTIF_H

#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include "Buildable.h"

/** @class DialogoAutentif
 * Esta clase agrupa las cosas mínimas necesarias para restringir acceso.
 * Solicita el password de acceso, y retorna éxito o fracaso en la
 * autentificación.
 */
class DialogoAutentif : public Gtk::Dialog, public Buildable {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        DialogoAutentif(BaseObjectType* cobject,
                        const Glib::RefPtr< Gtk::Builder >& builder);
        ~DialogoAutentif();
    private:
        Gtk::Entry* pEntryPassword;


        /**
         * Signal handler para signal_show.
         *
         * Llama a Gtk::Dialog::on_show() y luego borra el texto en la
         * pEntryPassword.
         */
        void on_show();

        /**
         * Signal handler para el click sobre el botón "Aceptar".
         *
         * Verifica si la contraseña ingresa es correcta. Si lo es, emite la
         * respuesta Gtk::RESPONSE_OK. Si no, informa con un diálogo y emite
         * Gtk::RESPONSE_CANCEL
         *
         * Por último, si no ingresó nada, emite Gtk::RESPONSE_CANCEL.
         */
        void on_aceptar_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Cancelar".
         *
         * Emite la respuesta Gtk::RESPONSE_CANCEL.
         */
        void on_cancelar_button_clicked();
};

#endif  // DIALOGO_AUTENTIF_H
