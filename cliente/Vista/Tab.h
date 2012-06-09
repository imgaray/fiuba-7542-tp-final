#ifndef TAB_H__
#define TAB_H__

#include <glibmm/ustring.h>
#include <gtkmm/box.h>
#include "PadreDeConsultantes.h"

class Tab : public Gtk::VBox, public PadreDeConsultantes {
    public:
        /** int i para diferenciar mejor del otro constructor */
        Tab(int i, const Glib::ustring& etiqueta);
        explicit Tab(const std::string& xml);
        ~Tab();

        const Glib::ustring& getEtiqueta();

        void hacerConsulta();
    private:
        Glib::ustring etiqueta;
};

#endif  // TAB_H__
