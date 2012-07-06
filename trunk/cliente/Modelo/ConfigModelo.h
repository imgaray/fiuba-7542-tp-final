#ifndef CONFIG_MODELO_H
#define CONFIG_MODELO_H

#include <gtkmm/box.h>
#include <gtkmm/toolbutton.h>
#include "Serializable.h"

typedef std::pair< Gtk::VBox*, Gtk::ToolButton* > filtradoresHandlers;

class ConfigModelo : public sigc::trackable , public Serializable {
    public:
        ConfigModelo(const Glib::ustring& label);
        ~ConfigModelo();

        void desconectar();

        Glib::ustring getLabel() const;
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

        virtual void desconectarDeHijo() = 0;
};

#endif  // CONFIG_MODELO_H


