#ifndef TAB_CONFIG_VISTA_H
#define TAB_CONFIG_VISTA_H

#include <gtkmm/table.h>
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>

class TabConfigModelo;

class TabConfigVista : public Gtk::Table {
    public:
        TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~TabConfigVista();

        void setModelo(TabConfigModelo* pModeloNuevo);

        Glib::ustring getTabLabel() const;
    private:
        Glib::RefPtr< Gtk::Builder > builder;
        Gtk::Entry* pEntryTabLabel;

        TabConfigModelo* pModelo;
};

#endif  // TAB_CONFIG_VISTA_H
