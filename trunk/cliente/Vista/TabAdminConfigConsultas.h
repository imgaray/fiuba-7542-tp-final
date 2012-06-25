#ifndef TAB_ADMIN_CONFIG_CONSULTAS_H
#define TAB_ADMIN_CONFIG_CONSULTAS_H

#include "TabAdminConfig.h"
#include <map>
#include <list>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>

class ConfigModelo;
class TabConfigVista;
class AdminConfigObjManager;

class TabAdminConfigConsultas : public TabAdminConfig {
    public:
        TabAdminConfigConsultas(BaseObjectType* cobject,
                           const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfigConsultas();

        bool aplicarCambios();
    private:
        AdminConfigObjManager* objManager;
        void on_tab_model_changed(ConfigModelo* m);

        void initBotones();
        void initTabConfig();

        std::map< const char*, Gtk::Button* > botones;
        Gtk::ComboBoxText comboTabSelec;
        TabConfigVista* pTabVista;
};

#endif  // TAB_ADMIN_CONFIG_CONSULTAS_H

