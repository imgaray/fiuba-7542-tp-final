#ifndef ADMIN_CONFIG_OBJ_MANAGER_H
#define ADMIN_CONFIG_OBJ_MANAGER_H

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
class TabConfigModelo;

/** @class clase encargada de manejar la parte de agregado de objetos dinámicos
 * por el admin (pestañas y paneles)
 * Emite la señal signal_model_changed cuando el modelo que está detrás de la
 * vista cambia
 */
class AdminConfigObjManager : public sigc::trackable {
    public:
        AdminConfigObjManager(Gtk::ComboBoxText* cbtext,
                              Gtk::Button* pAceptar,
                              Gtk::Button* pGuardarCambios,
                              Gtk::Button* pEliminar,
                              const Glib::ustring& def);
        ~AdminConfigObjManager();

        TabConfigModelo* getModelo() const;

        sigc::signal< void, TabConfigModelo* > signal_model_changed();
    private:
        sigc::signal< void, TabConfigModelo* > _signal_model_changed;
        enum t_boton {
            B_ACEPTAR,
            B_GUARDAR,
            B_ELIMINAR
        };

        std::map< t_boton, Gtk::Button* > botones;

        void on_agregar_button_clicked();
        void on_guardar_cambios_button_clicked();
        void on_eliminar_button_clicked();

        Glib::ustring nombre_por_defecto;

        std::list< TabConfigModelo* > consultasConfiguradas;
        // para una búsqueda más rápida
        std::map< Glib::ustring, TabConfigModelo* > mapaConsultasConfiguradas;
        TabConfigModelo* pTabModeloActual;
        bool guardandoCambios;
        void on_combo_selec_changed();
        Gtk::ComboBoxText* comboSelec;
};

#endif  // ADMIN_CONFIG_OBJ_MANAGER_H
