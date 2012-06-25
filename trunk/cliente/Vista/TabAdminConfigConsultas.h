#ifndef TAB_ADMIN_CONFIG_CONSULTAS_H
#define TAB_ADMIN_CONFIG_CONSULTAS_H

#include "TabAdminConfig.h"
#include <map>
#include <list>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>

class TabConfigModelo;
class TabConfigVista;

class TabAdminConfigConsultas : public TabAdminConfig {
    public:
        TabAdminConfigConsultas(BaseObjectType* cobject,
                           const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfigConsultas();

        bool aplicarCambios();
    private:
        /** botones */
        void initBotones();
        std::map< const char*, Gtk::Button* > botones;
        void on_agregar_tab_button_clicked();
        void on_guardar_cambios_tab_button_clicked();
        void on_eliminar_tab_button_clicked();


        void initTabConfig();
        Gtk::ComboBoxText comboTabSelec;

        std::list< TabConfigModelo* > consultasConfiguradas;
        // para una búsqueda más rápida
        std::map< Glib::ustring, TabConfigModelo* > mapaConsultasConfiguradas;
        TabConfigModelo* pTabModeloActual;
        TabConfigVista* pTabVista;
        bool guardandoCambios;
        void on_combo_tab_selec_changed();
};

#endif  // TAB_ADMIN_CONFIG_CONSULTAS_H

