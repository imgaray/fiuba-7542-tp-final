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
         sigc::signal< void > signal_navegabilidad();
         sigc::signal< void, bool > signal_input_disponible();
    protected:
        Gtk::ComboBoxText valores;
        bool valido;
        Tab* tabPadre;

        sigc::signal< void > signal_navegabilidad_seleccionada;
        sigc::signal< void, bool > _signal_input_disponible;

    private:
        Gtk::VSeparator sep;
};

#endif  // FILTRADOR_INPUT_H
