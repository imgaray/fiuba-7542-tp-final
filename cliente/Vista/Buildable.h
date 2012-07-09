#ifndef BUILDABLE_H
#define BUILDABLE_H

#include <gtkmm/builder.h>
#include "ExcepcionArchivoGladeCorrupto.h"

/**
 * @class Buildable
 * Clase "helper" para todas las que se construyen desde un archivo GLADE
 * tengan métodos más limpios que, además de conseguir la referencia al
 * objeto buscado, verifiquen la existencia y lancen la excepción pertinente
 */

class Buildable {
    public:
        /**
         * @brief constructor, crea la referencia al Gtk::Builder
         * @param builder referencia a la instancia que lo construye
         */
        Buildable(const Glib::RefPtr< Gtk::Builder >& _builder)
        : builder(_builder) {}

    protected:
        Glib::RefPtr< Gtk::Builder > builder;

        /**
         * @brief wrapper a Gtk::Builder::get_widget(const Glib::ustring& , T_Widget*& )
         * @param nombre    nombre del objeto a obtener
         * @retval pWidget  puntero al objeto buscado
         * @throw instancia de ExcepcionArchivoGladeCorrupto(nombre)
         */
        template< typename T_Widget >
        void get_widget(const Glib::ustring& nombre, T_Widget*& pWidget) {
            builder->get_widget(nombre, pWidget);
            if (!pWidget)
                throw ExcepcionArchivoGladeCorrupto(nombre);
        }

        /**
         * @brief wrapper a Gtk::Builder::get_widget_derived(const Glib::ustring& , T_Widget*& )
         * @param nombre    nombre del objeto a obtener
         * @retval pWidget  puntero al objeto buscado
         * @throw instancia de ExcepcionArchivoGladeCorrupto(nombre)
         */
        template< typename T_Widget >
        void get_widget_derived(const Glib::ustring& nombre, T_Widget*& pWidget) {
            builder->get_widget_derived(nombre, pWidget);
            if (!pWidget)
                throw ExcepcionArchivoGladeCorrupto(nombre);
        }
};

#endif  // BUILDABLE_H
