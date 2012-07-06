#ifndef ADMIN_CONFIG_OBJ_MANAGER_H
#define ADMIN_CONFIG_OBJ_MANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include "Serializable.h"

class ConfigModelo;
class TabConfigModelo;
class PanelConfigModelo;

enum t_Objeto {
    OBJ_TAB,
    OBJ_PANEL
};
/** @class AdminConfigObjManager
 * clase encargada de manejar la parte de agregado de objetos dinámicos
 * por el admin (pestañas y paneles)
 * Emite la señal signal_model_changed cuando el modelo que está detrás de la
 * vista cambia
 */
class AdminConfigObjManager : public sigc::trackable , public Serializable {
    public:
        AdminConfigObjManager(t_Objeto tipo,
                              Gtk::ComboBoxText* cbtext,
                              Gtk::Entry* pEntry,
                              Gtk::Button* pAceptar,
                              Gtk::Button* pGuardarCambios,
                              Gtk::Button* pEliminar,
                              const Glib::ustring& def);
        ~AdminConfigObjManager();

        void desconectar();
        void reconectar();

        ConfigModelo* getModelo() const;

        std::list< TabConfigModelo* > getModelosComoTabs();
        std::list< PanelConfigModelo* > getModelosComoPaneles();

        sigc::signal< void, ConfigModelo* > signal_model_changed();
        sigc::signal< void, ConfigModelo* > signal_model_saved();
        sigc::signal< void, ConfigModelo* > signal_model_deleted();


        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    private:
        sigc::signal< void, ConfigModelo* > _signal_model_changed;
        sigc::signal< void, ConfigModelo* > _signal_model_saved;
        sigc::signal< void, ConfigModelo* > _signal_model_deleted;
        enum t_boton {
            B_AGREGAR,
            B_GUARDAR,
            B_ELIMINAR
        };
        t_Objeto tipo;
        ConfigModelo* new_modelo();

        /** conexiones a las señales */
        sigc::connection connectionCombobox;
        sigc::connection connectionEntryLabel;
        sigc::connection connectionEntryLabelFocusIn;
        sigc::connection connectionEntryLabelFocusOut;
        sigc::connection connectionButtonAgregar;
        sigc::connection connectionButtonGuardar;
        sigc::connection connectionButtonEliminar;

        Gtk::ComboBoxText* comboSelec;
        Gtk::Entry* pEntryLabel;
        std::map< t_boton, Gtk::Button* > botones;

        void on_combo_selec_changed();
        void on_entry_label_activate();
        bool on_entry_label_focus_in(GdkEventFocus* e);
        bool on_entry_label_focus_out(GdkEventFocus* e);
        void on_agregar_button_clicked();
        void on_guardar_cambios_button_clicked();
        void on_eliminar_button_clicked();

        Glib::ustring nombre_por_defecto;

        std::list< ConfigModelo* > consultasConfiguradas;
        // para una búsqueda más rápida
        std::map< Glib::ustring, ConfigModelo* > mapaConsultasConfiguradas;
        ConfigModelo* pModeloActual;
        bool guardandoCambios;
};

#endif  // ADMIN_CONFIG_OBJ_MANAGER_H
