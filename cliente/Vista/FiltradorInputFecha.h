#ifndef FILTRADOR_INPUT_FECHA_H
#define FILTRADOR_INPUT_FECHA_H

#include "FiltradorInput.h"
#include <gtkmm/entry.h>
#include "Utilitario.h"
#include "M_Fechas.h"

#ifndef NO_PERTENECE
#define NO_PERTENECE -1
#endif

class FiltradorInputFecha : public FiltradorInput {
    public:
        FiltradorInputFecha(const Glib::ustring& input);
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
         * @brief Signal handler para el cambio de la selección en el combobox.
         *
         * Actualiza el número de fila seleccionada (int FiltradorInputFecha::i).
         */
        void on_combo_changed();

        /**
         * @brief Signal handler para la activación de la entrada de texto (al apretar "enter")
         *
         * Valida el ingreso y emite FiltradorInput::_signal_input_disponible
         * si cambió su estado de disponibilidad.
         */
        void on_entry_activated();
};

#endif  // FILTRADOR_INPUT_FECHA_H
