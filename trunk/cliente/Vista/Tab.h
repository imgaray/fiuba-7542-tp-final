#ifndef TAB_H__
#define TAB_H__

#include <glibmm/ustring.h>
#include <gtkmm/table.h>

class Tab : public Gtk::Table {
    public:
        Tab(int x, int y, bool homog, const Glib::ustring& etiqueta);
        explicit Tab(const std::string& xml);
        ~Tab();
        const Glib::ustring& getEtiqueta();
    private:
        Glib::ustring etiqueta;
};

#endif  // TAB_H__
