#ifndef DIALOGO_AUTENTIF_H
#define DIALOGO_AUTENTIF_H

#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>

class DialogoAutentif : public Gtk::Dialog {
    public:
        DialogoAutentif(BaseObjectType* cobject,
                        const Glib::RefPtr< Gtk::Builder >& builder);
        ~DialogoAutentif();
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        Gtk::Entry* pEntryPassword;

        void on_aceptar_button_clicked();
        void on_cancelar_button_clicked();
};

#endif  // DIALOGO_AUTENTIF_H
