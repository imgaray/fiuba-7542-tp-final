#ifndef TAB_CONFIG_VISTA_H
#define TAB_CONFIG_VISTA_H

#include <gtkmm/table.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>

class TabConfigModelo;

class TabConfigVista : public Gtk::Table {
    public:
        TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabConfigVista();

        void setModelo(TabConfigModelo* pModeloNuevo);
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        Gtk::Entry* pEntryTabLabel;
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;

        TabConfigModelo* pModelo;
};

#endif  // TAB_CONFIG_VISTA_H
