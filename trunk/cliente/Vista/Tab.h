#ifndef TAB_H__
#define TAB_H__

#include <glibmm/ustring.h>
#include <gtkmm/box.h>

class Tab : public Gtk::VBox {
    public:
        Tab(int i, const Glib::ustring& etiqueta);
        explicit Tab(const std::string& xml);
        ~Tab();
        const Glib::ustring& getEtiqueta();
    private:
        Glib::ustring etiqueta;
};

#endif  // TAB_H__
