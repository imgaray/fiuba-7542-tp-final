#ifndef FILTRADOR_INPUT_FECHA_H
#define FILTRADOR_INPUT_FECHA_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>

#ifndef NO_PERTENECE
#define NO_PERTENECE -1
#endif

class FiltradorInputFecha : public FiltradorInput {
    public:
        FiltradorInputFecha(const Glib::ustring& input);
        ~FiltradorInputFecha();

        static int perteneceAlCombobox(const Glib::ustring& valor);
        /// Validador de la entrada (Gtk::Entry)
        static bool esValido(const Glib::ustring& valor);

        Consulta& filtrar(Consulta& c);
    private:
        Gtk::Entry entrada;
        static Glib::ustring valoresCombo[];
};

#endif  // FILTRADOR_INPUT_FECHA_H
