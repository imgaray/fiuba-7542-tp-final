#ifndef FILTRADOR_HELPER_H
#define FILTRADOR_HELPER_H

#define NO_PERTENECE -1

#include <gtkmm/comboboxtext.h>
#include "Definiciones.h"

class FiltradorHelper {
    public:
        static const FiltradorHelper& getInstancia();

        void popularComboFecha(Gtk::ComboBoxText* combo) const;
        void popularComboHechoInput(Gtk::ComboBoxText* combo) const;
        void popularComboAgregaciones(Gtk::ComboBoxText* combo) const;

        int perteneceAlComboFecha(const Glib::ustring& valor) const;
        int perteneceAlComboHechoInput(const Glib::ustring& valor) const;
        int perteneceAlAgregacionesPosibles(const Glib::ustring& valor) const;

        Fecha validarFecha(int i_combo, const Glib::ustring& valor) const;
        Glib::ustring validarHecho(int i_combo, const Glib::ustring& valor) const;

    private:
        FiltradorHelper();
        static FiltradorHelper instancia;

        // valores posibles de los combobox
        static Glib::ustring comboFecha[];
        static Glib::ustring comboHechoInput[];
        static Glib::ustring agregPosibles[];

        void popularCombo(Gtk::ComboBoxText* combo,
                          Glib::ustring valores[], int size) const;
        int perteneceAlCombo(const Glib::ustring& valor,
                             Glib::ustring valores[], int size) const;
};

#endif  // FILTRADOR_HELPER_H
