#ifndef FILTRADOR_INPUT_FECHA_H
#define FILTRADOR_INPUT_FECHA_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>
#include "Definiciones.h"

/** @class FiltradorInputFecha
 * Input de tipo fecha.
 */
class FiltradorInputFecha : public FiltradorInput {
    public:
        /**
         * Constructor.
         * @param input nombre del campo fecha
         */
        FiltradorInputFecha(const Glib::ustring& input);
        /**
         * Destructor.
         */
        ~FiltradorInputFecha();

        void recibirNavegacionSeleccionada(const Glib::ustring& input,
                                           const Glib::ustring& valor);

        void filtrar(Consulta& c);
    private:
        Gtk::Entry entrada;
        Gtk::Label infoError;
        int i;  // iésimo valor del combobox posible
        Fecha f;


        /**
         * Signal handler para el cambio de la selección en el combobox.
         *
         * Actualiza el número de fila seleccionada
         * (int FiltradorInputFecha::i).
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

#endif  // FILTRADOR_INPUT_FECHA_H
