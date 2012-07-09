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

class TabConfigVista : public Gtk::VBox, public Buildable  {
    public:
        /**
         * @brief Constructor requerido para construir con Gtk::Builder..
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
