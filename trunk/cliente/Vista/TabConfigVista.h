#ifndef TAB_CONFIG_VISTA_H
#define TAB_CONFIG_VISTA_H

#include <gtkmm/table.h>
#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/checkbutton.h>
#include "Buildable.h"

class TabConfigModelo;
class PanelConfigModelo;
class PanelConfigVista;


/** @class TabConfigVista
 * Clase que representa la vista de configuración de pestañas. Si no está
 * asociada a un modelo de configuración de tabs, no tiene mucho sentido.
 *
 * Presenta:
 * -un combobox para elegir qué tab está siendo modificada
 * -tres botones, "Agregar", "Guardar cambios" y "Eliminar"
 * -una entrada para poner el nombre de la tab
 * -dos Gtk::SpinButtons para elegir el tamaño de la grilla
 * -sector de filtradores que admiten sólo inputs
 * -un PanelConfigVista para configurar los paneles
 */
class TabConfigVista : public Gtk::VBox, public Buildable  {
    public:
        /**
         * Constructor requerido para construir con Gtk::Builder.
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabConfigVista();

        void setModelo(TabConfigModelo* pModeloNuevo);
    private:
        void initBotones();
        void initPanelConfig();

        TabConfigModelo* pModelo;
        sigc::connection connectionTabModelo;

        /**
         * Signal handler para TabConfigModelo::signal_panel_model_changed,
         * emitida cuando el panel seleccionado cambia.
         *
         * Escribe en la entrada del nombre del panel el nombde de m, y le
         * informa del cambio de modelo a la vista de la configuración del
         * panel (void PanelConfigModelo::setModelo(PanelConfigModelo* )).
         * @param m modelo nuevo para la vista de configuración de panel
         */
        void on_panel_model_changed(PanelConfigModelo* m);

        PanelConfigVista* pPanelVista;

        std::map< const char*, Gtk::Button* > botones;
        Gtk::ComboBoxText comboPanelSelec;

        Gtk::Entry* pEntryPanelLabel;
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;

        Gtk::VBox* pInputs;
        Gtk::ToolButton* pBotonAgregarInput;
};

#endif  // TAB_CONFIG_VISTA_H
