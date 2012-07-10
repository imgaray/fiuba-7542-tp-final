#ifndef TAB_ADMIN_CONFIG_H
#define TAB_ADMIN_CONFIG_H

#include <gtkmm/box.h>
#include "Buildable.h"

/** @class TabAdminConfig
 * Clase que propone una interfaz para las pestrañas de la ventana de
 * configuración del admin.
 */
class TabAdminConfig : public Gtk::VBox, public Buildable  {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabAdminConfig(BaseObjectType* cobject,
                  const Glib::RefPtr< Gtk::Builder >& builder);
        /**
         * Destructor.
         */
        ~TabAdminConfig();

        /**
         *@return true si el estado de la pestaña es válido para guardar
         */
        virtual bool aplicarCambios() = 0;
};

#endif  // TAB_ADMIN_CONFIG_H

