#ifndef CONFIG_MODELO_H
#define CONFIG_MODELO_H

#include <gtkmm/entry.h>

class ConfigModelo {
    public:
        ConfigModelo(const Glib::ustring& label);
        ~ConfigModelo();

        void desconectar();
        void setEntryLabel(Gtk::Entry* pEntry);

        Glib::ustring getLabel() const;
        Glib::ustring getLabelNueva() const;
        void setLabelNuevaComoValida();
    private:
        Glib::ustring label;
        sigc::connection connectionEntryLabel;
        virtual void on_entry_label_changed();
        Gtk::Entry* pEntryLabel;

        virtual void desconectarDeHijo() = 0;
};

#endif  // CONFIG_MODELO_H


