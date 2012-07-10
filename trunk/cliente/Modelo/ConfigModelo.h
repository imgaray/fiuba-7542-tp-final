#ifndef CONFIG_MODELO_H
#define CONFIG_MODELO_H

#include <gtkmm/box.h>
#include <gtkmm/toolbutton.h>
#include "Serializable.h"

typedef std::pair< Gtk::VBox*, Gtk::ToolButton* > filtradoresHandlers;


/** @class ConfigModelo
 * Clase base para los modelos que están detrás de las vistas de configuración.
 *
 * Como hay una vista y muchos modelos, tiene la capacidad de desconectarse y
 * reconectarse (cuando le pasan las referencias a la vista).
 *
 * Identificable por su Glib::ustring label modificable, difieren de los
 * configModelo de los filtradores en eso principalmente.
 */
class ConfigModelo : public sigc::trackable , public Serializable {
    public:
        /**
         * Constructor.
         */
        ConfigModelo(const Glib::ustring& label);
        /**
         * Destructor.
         */
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


