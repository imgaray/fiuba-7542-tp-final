#ifndef DIALOGO_AUTENTIF_H
#define DIALOGO_AUTENTIF_H

#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include "Buildable.h"

class DialogoAutentif : public Gtk::Dialog, public Buildable {
    public:
        /**
         * @brief constructor requerido para construir con Gtk::Builder
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        DialogoAutentif(BaseObjectType* cobject,
                        const Glib::RefPtr< Gtk::Builder >& builder);
        ~DialogoAutentif();
    private:
        Gtk::Entry* pEntryPassword;

        void on_show();
        void on_aceptar_button_clicked();
        void on_cancelar_button_clicked();
};

#endif  // DIALOGO_AUTENTIF_H
