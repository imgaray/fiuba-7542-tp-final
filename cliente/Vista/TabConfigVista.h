#ifndef TAB_CONFIG_VISTA_H
#define TAB_CONFIG_VISTA_H

#include <gtkmm/table.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>

class TabConfigModelo;
class PanelConfigVista;

class TabConfigVista : public Gtk::Table {
    public:
        TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabConfigVista();

        void setModelo(TabConfigModelo* pModeloNuevo);
    private:
        void initBotones();
        void initPanelConfig();

        std::map< const char*, Gtk::Button* > botones;
        Gtk::ComboBoxText comboPanelSelec;

        Glib::RefPtr< Gtk::Builder > builder;
        Gtk::Entry* pEntryTabLabel;
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;

        TabConfigModelo* pModelo;
//        PanelConfigVista* pPanelVista;
};

#endif  // TAB_CONFIG_VISTA_H
