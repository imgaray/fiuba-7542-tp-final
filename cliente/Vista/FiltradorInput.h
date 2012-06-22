#ifndef FILTRADOR_INPUT_H
#define FILTRADOR_INPUT_H

#include "Filtrador.h"
#include <gtkmm/separator.h>
#include <gtkmm/comboboxtext.h>

class Tab;

class FiltradorInput : public Filtrador {
    public:
        FiltradorInput(const Glib::ustring& input);
        virtual ~FiltradorInput();

        virtual void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                            const Glib::ustring& valor) = 0;
        void setTabPadre(Tab* padre);
    protected:
        Gtk::ComboBoxText valores;
        bool valido;
        Tab* tabPadre;

    private:
        Gtk::VSeparator sep;
};

#endif  // FILTRADOR_INPUT_H
