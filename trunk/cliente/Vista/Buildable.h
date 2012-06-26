#ifndef BUILDABLE_H
#define BUILDABLE_H

#include <gtkmm/builder.h>
#include "ExcepcionArchivoGladeCorrupto.h"

class Buildable {
    public:
        Buildable(const Glib::RefPtr< Gtk::Builder >& _builder)
        : builder(_builder) {}

    protected:
        Glib::RefPtr< Gtk::Builder > builder;

        template< typename T_Widget >
        void get_widget(const Glib::ustring& nombre, T_Widget*& pWidget) {
            builder->get_widget(nombre, pWidget);
            if (!pWidget)
                throw ExcepcionArchivoGladeCorrupto(nombre);
        }

        template< typename T_Widget >
        void get_widget_derived(const Glib::ustring& nombre, T_Widget*& pWidget) {
            builder->get_widget_derived(nombre, pWidget);
            if (!pWidget)
                throw ExcepcionArchivoGladeCorrupto(nombre);
        }
};

#endif  // BUILDABLE_H
