#ifndef TAB_ADMIN_CONFIG_H
#define TAB_ADMIN_CONFIG_H

#include <gtkmm/box.h>
#include "Buildable.h"

class TabAdminConfig : public Gtk::VBox, public Buildable  {
    public:
        TabAdminConfig(BaseObjectType* cobject,
                  const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfig();

        // retorna true si el estado de la pestaña es válido para guardar
        virtual bool aplicarCambios() = 0;
};

#endif  // TAB_ADMIN_CONFIG_H

