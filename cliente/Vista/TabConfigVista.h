#ifndef TAB_CONFIG_VISTA_H
#define TAB_CONFIG_VISTA_H

#include <gtkmm/table.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/checkbutton.h>
#include "Buildable.h"

class TabConfigModelo;
class PanelConfigModelo;
class PanelConfigVista;

class TabConfigVista : public Gtk::Table, public Buildable  {
    public:
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

        Gtk::Entry* pEntryTabLabel;
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;
        std::list< Gtk::CheckButton* > pCheckButtonsFiltradores;
};

#endif  // TAB_CONFIG_VISTA_H
