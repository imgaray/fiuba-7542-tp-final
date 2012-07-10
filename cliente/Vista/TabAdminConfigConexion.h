#ifndef TAB_ADMIN_CONFIG_CONEXION_H
#define TAB_ADMIN_CONFIG_CONEXION_H

#include "TabAdminConfig.h"
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>

/** @class TabAdminConfigConexion
 * Pestaña del admin para configurar el servidor.
 */
class TabAdminConfigConexion : public TabAdminConfig {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabAdminConfigConexion(BaseObjectType* cobject,
                  const Glib::RefPtr< Gtk::Builder >& builder);
        /**
         * Destructor.
         */
        ~TabAdminConfigConexion();

        bool aplicarCambios();
    private:
        Gtk::Entry* pEntryIP;
        Gtk::SpinButton* pSpinButtonPuerto;
};

#endif  // TAB_ADMIN_CONFIG_CONEXION_H
