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

        void setArchivoPersonalizador(const char* archivo);

        bool aplicarCambios();
    private:
        AdminConfigObjManager* tabManager;
        void on_tab_model_changed(ConfigModelo* m);


        void cargarConsultas(const char* ruta);

        void initBotones();
        void initTabConfig();

        std::map< const char*, Gtk::Button* > botones;
        Gtk::ComboBoxText comboTabSelec;
        TabConfigVista* pTabVista;

        Glib::ustring rutaArchivo;
};

#endif  // TAB_ADMIN_CONFIG_CONSULTAS_H

