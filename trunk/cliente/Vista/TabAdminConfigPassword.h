#ifndef TAB_ADMIN_CONFIG_PASSWORD_H
#define TAB_ADMIN_CONFIG_PASSWORD_H

#include "TabAdminConfig.h"
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>

class TabAdminConfigPassword : public TabAdminConfig {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabAdminConfigPassword(BaseObjectType* cobject,
                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfigPassword();

        bool aplicarCambios();

        void limpiar_pass_entries();
    private:
        Gtk::Entry* pEntryPassActual;
        Gtk::Entry* pEntryPassNueva;
};

#endif  // TAB_ADMIN_CONFIG_PASSWORD_H

