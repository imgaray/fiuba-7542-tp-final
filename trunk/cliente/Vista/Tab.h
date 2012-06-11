#ifndef TAB_H__
#define TAB_H__

#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class Tab : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** int i para diferenciar mejor del otro constructor */
        Tab(int i, const Glib::ustring& etiqueta);
        explicit Tab(const std::string& xml);
        ~Tab();

        Gtk::HBox& getEtiqueta();

        void agregarConsultante(PadreDeConsultantes* c);
    private:
        Gtk::HBox etiquetaCompuesta;
        Gtk::Label etiqueta;
        Gtk::Spinner s;
};

#endif  // TAB_H__
