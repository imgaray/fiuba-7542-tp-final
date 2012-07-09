#ifndef TAB_ADMIN_CONFIG_CONEXION_H
#define TAB_ADMIN_CONFIG_CONEXION_H

#include "TabAdminConfig.h"
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>

class TabAdminConfigConexion : public TabAdminConfig {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabAdminConfigConexion(BaseObjectType* cobject,
                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfigConexion();

        bool aplicarCambios();
    private:
        Gtk::Entry* pEntryIP;
        Gtk::SpinButton* pSpinButtonPuerto;

        void on_entry_ip_changed();
};

#endif  // TAB_ADMIN_CONFIG_CONEXION_H
