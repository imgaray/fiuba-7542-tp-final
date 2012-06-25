#ifndef CONFIG_MODELO_H
#define CONFIG_MODELO_H

#include <gtkmm/entry.h>

class ConfigModelo {
    public:
        ConfigModelo(const Glib::ustring& label);
        ~ConfigModelo();

        void desconectar();
        void setEntryTabLabel(Gtk::Entry* pEntry);

        Glib::ustring getTabLabel() const;
        Glib::ustring getTabLabelNueva() const;
        void setTabLabelNuevaComoValida();
    private:
        Glib::ustring tabLabel;
        sigc::connection connectionEntryTabLabel;
        virtual void on_entry_tab_label_changed();
        Gtk::Entry* pEntryTabLabel;

        virtual void desconectarDeHijo() = 0;
};

#endif  // CONFIG_MODELO_H


