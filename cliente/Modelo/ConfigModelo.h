#ifndef CONFIG_MODELO_H
#define CONFIG_MODELO_H

#include <gtkmm/entry.h>
#include <gtkmm/box.h>
#include <gtkmm/toolbutton.h>

typedef std::pair< Gtk::VBox*, Gtk::ToolButton* > filtradoresHandlers;

class ConfigModelo : public sigc::trackable {
    public:
        ConfigModelo(const Glib::ustring& label);
        ConfigModelo();
        ~ConfigModelo();

        void desconectar();
        void setEntryLabel(Gtk::Entry* pEntry);

        Glib::ustring getLabel() const;
        Glib::ustring getLabelNueva() const;
        void setLabel(const Glib::ustring& label);
    protected:
        template < typename T_Widget >
        void desconectar(sigc::connection& conex, T_Widget*& pAlgo) {
            if (pAlgo) {
                conex.disconnect();
                pAlgo = NULL;
            }
        }

    private:
        Glib::ustring label;
        sigc::connection connectionEntryLabel;
        virtual void on_entry_label_changed();
        Gtk::Entry* pEntryLabel;

        virtual void desconectarDeHijo() = 0;
};

#endif  // CONFIG_MODELO_H


