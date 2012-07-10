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
 * Clase encargada de manejar la parte de agregado de objetos dinámicos
 * por el admin (pestañas y paneles).
 *
 * Emite las señaesl:
 * -signal_model_changed cuando el modelo que está detrás de la vista cambia.
 * -signal_model_deleted cuando el modelo seleccionado fue eliminado
 * -signal_model_saved   cuando el modelo seleccionado guarda sus cambios
 */
class AdminConfigObjManager : public sigc::trackable , public Serializable {
    public:
        /**
         * Constructor.
         */
        AdminConfigObjManager(t_Objeto tipo,
                              Gtk::ComboBoxText* cbtext,
                              Gtk::Entry* pEntry,
                              Gtk::Button* pAceptar,
                              Gtk::Button* pGuardarCambios,
                              Gtk::Button* pEliminar,
                              const Glib::ustring& def);
        /**
         * Destructor. Libera todos los ConfigModelo instanciados en el heap
         */
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

        /* conexiones a las señales */
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

        /**
         * Signal handler para el cambio del combobox que elige el modelo
         * activo del manager
         *
         * Establece la visibilidad de los botones "Agregar", "Guardar cambios"
         * y "Eliminar" según si el modelo seleccionado existe o no. Fija el
         * modelo seleccionado y emite la señal de cambio de modelo,
         * _signal_model_changed.
         */
        void on_combo_selec_changed();

        /**
         * Signal handler para la activación de la Gtk::Entry donde se ingresa
         * el nombre del modelo seleccionado.
         *
         * Al apretar "enter", simula que se presionó el botón "Agregar" o
         * "Guardar cambios" según corresponda.
         */
        void on_entry_label_activate();

        /**
         * Signal handler para la recepción del foco de la Gtk::Entry donde
         * se ingresa el nombre del modelo seleccionado.
         *
         * Si está ingresado el nombre por defecto, lo borra.
         * @param e características del foco
         * @return true siempre, el manejo del evento termina acá.
         */
        bool on_entry_label_focus_in(GdkEventFocus* e);

        /**
         * Signal handler para la pérdida del foco de la Gtk::Entry donde se
         * ingresa el nombre del modelo seleccionado.
         *
         * Si no hay nada ingresado, vuelve a escribir el nombre por defecto
         * @param e características del foco
         * @return true siempre, el manejo del evento termina acá.
         */
        bool on_entry_label_focus_out(GdkEventFocus* e);

        /**
         * Signal handler para el click sobre el botón "Agregar".
         *
         * Verifica que el nombre ingresado esté permitido, sea porque no
         * es el nombre por defecto o porque no pertenece a otro objeto ya,
         * y lo añade a los contenedores.
         */
        void on_agregar_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Guardar cambios".
         *
         * Valida los cambios que deban ser validados del modelo actual,
         * por ejemplo, cambios en el nombre, y los guarda.
         */
        void on_guardar_cambios_button_clicked();

        /**
         * Signal handler para el click sobre el botón "Eliminar".
         *
         * Elimina el modelo seleccionado.
         */
        void on_eliminar_button_clicked();

        Glib::ustring nombre_por_defecto;

        std::list< ConfigModelo* > consultasConfiguradas;
        // para una búsqueda más rápida
        std::map< Glib::ustring, ConfigModelo* > mapaConsultasConfiguradas;
        ConfigModelo* pModeloActual;
        bool guardandoCambios;
};

#endif  // ADMIN_CONFIG_OBJ_MANAGER_H
