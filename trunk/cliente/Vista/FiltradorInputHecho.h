#ifndef FILTRADOR_INPUT_HECHO_H
#define FILTRADOR_INPUT_HECHO_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>

/** @class FiltradorInputHecho
 * Input de tipo hecho.
 */
class FiltradorInputHecho : public FiltradorInput {
    public:
        /**
         * Constructor.
         * @param input nombre del hecho
         */
        FiltradorInputHecho(const Glib::ustring& input);
        /**
         * Destructor.
         */
        ~FiltradorInputHecho();

        void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                           const Glib::ustring& valor);

        void filtrar(Consulta& c);
    private:
        Gtk::Entry entrada;
        int i;  // iésimo valor del combobox posible
        Glib::ustring valorHecho;


        /**
         * Signal handler para el cambio de la selección en el combobox.
         *
         * Actualiza el número de fila seleccionada
         * (int FiltradorInputHecho::i).
         */
        void on_combo_changed();

        /**
         * Signal handler para la activación de la entrada de texto (al
         * apretar "enter")
         *
         * Valida el ingreso y emite FiltradorInput::_signal_input_disponible
         * si cambió su estado de disponibilidad.
         */
        void on_entry_activated();
};

#endif  // FILTRADOR_INPUT_HECHO_H
