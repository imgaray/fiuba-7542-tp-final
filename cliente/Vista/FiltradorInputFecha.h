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
        /** Validador de la entrada (Gtk::Entry)
         * i: el iésimo valor del combobox
         * retorna la fecha bien construida, o STR_NULA si no era válida
         */
        static Fecha validar(int i, const Glib::ustring& valor);

        Consulta& filtrar(Consulta& c);
    private:
        Gtk::Entry entrada;
        static Glib::ustring valoresCombo[];
        int i;  // iésimo valor del combobox posible
        Fecha f;

        // handler para cuando el combobox cambia su selección
        void on_combo_changed();
        // handler para cuando el usuario presiona "enter" estando en la Gtk::Entry
        void on_entry_activated();
};

#endif  // FILTRADOR_INPUT_FECHA_H
