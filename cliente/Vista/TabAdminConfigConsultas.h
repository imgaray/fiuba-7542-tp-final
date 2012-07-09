#ifndef TAB_ADMIN_CONFIG_CONSULTAS_H
#define TAB_ADMIN_CONFIG_CONSULTAS_H

#include "TabAdminConfig.h"
#include <map>
#include <list>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include "Personalizador.h"

class ConfigModelo;
class TabConfigVista;
class AdminConfigObjManager;

class TabAdminConfigConsultas : public TabAdminConfig {
    public:
        /**
         * @brief constructor requerido para construir con Gtk::Builder
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabAdminConfigConsultas(BaseObjectType* cobject,
                           const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabAdminConfigConsultas();

        void setArchivoPersonalizador(const char* archivo);
        void actualizarVDinamica(VentanaClienteDinamica* pVDinamica);

        bool aplicarCambios();
    private:
        AdminConfigObjManager* tabManager;
        Personalizador dynBuilder;

        void on_tab_model_changed(ConfigModelo* m);


        void cargarConsultas(const char* ruta);

        void initBotones();
        void initTabConfig();

        Gtk::ComboBoxText comboTabSelec;
        Gtk::Entry* pEntryTabLabel;
        std::map< const char*, Gtk::Button* > botones;
        TabConfigVista* pTabVista;

        Glib::ustring rutaArchivo;
};

#endif  // TAB_ADMIN_CONFIG_CONSULTAS_H

