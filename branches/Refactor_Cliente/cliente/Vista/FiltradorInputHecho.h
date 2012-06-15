#ifndef FILTRADOR_INPUT_HECHO_H
#define FILTRADOR_INPUT_HECHO_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>
#include "Utilitario.h"

#ifndef NO_PERTENECE
#define NO_PERTENECE -1
#endif

class FiltradorInputHecho : public FiltradorInput {
    public:
        FiltradorInputHecho(const Glib::ustring& input);
        ~FiltradorInputHecho();

        static int perteneceAlCombobox(const Glib::ustring& valor);
        /// Validador de la entrada (Gtk::Entry)
        static Glib::ustring validar(int i, const Glib::ustring& valor);

        Consulta& filtrar(Consulta& c);
    private:
        static Utilitario u;
        Gtk::Entry entrada;
        static Glib::ustring valoresCombo[];
        int i;  // iésimo valor del combobox posible
        Glib::ustring valorHecho;

        // handler para cuando el combobox cambia su selección
        void on_combo_changed();
        // handler para cuando el usuario presiona "enter" estando en la Gtk::Entry
        void on_entry_activated();
};

#endif  // FILTRADOR_INPUT_HECHO_H
