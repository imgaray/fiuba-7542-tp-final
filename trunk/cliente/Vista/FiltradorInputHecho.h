#ifndef FILTRADOR_INPUT_HECHO_H
#define FILTRADOR_INPUT_HECHO_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>

class FiltradorInputHecho : public FiltradorInput {
    public:
        FiltradorInputHecho(const Glib::ustring& input);
        ~FiltradorInputHecho();
        static bool perteneceAlCombobox(const Glib::ustring& valor);
        /// Validador de la entrada (Gtk::Entry)
        static bool esValido(const Glib::ustring& valor);
    private:
        Gtk::Entry entrada;
        static Glib::ustring valoresCombo[];
};

#endif  // FILTRADOR_INPUT_HECHO_H
