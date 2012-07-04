#ifndef FILTRADOR_CONFIG_MODELO_H
#define FILTRADOR_CONFIG_MODELO_H

#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/toolbutton.h>

class FiltradorConfigModelo {
    public:
        FiltradorConfigModelo();
        ~FiltradorConfigModelo();

        void setVista(Gtk::ComboBoxText* comboDimension,
                      Gtk::ComboBoxText* comboFecha,
                      Gtk::ComboBoxText* comboHecho,
                      Gtk::Entry* entryExtra,
                      Gtk::ToolButton* botonEliminar);

    protected:
        Gtk::ComboBoxText* comboDimension;
        Gtk::ComboBoxText* comboFecha;
        Gtk::ComboBoxText* comboHecho;
        Gtk::Entry* entryExtra;

    private:
        Gtk::ToolButton* botonEliminar;

        void setComboDimension(Gtk::ComboBoxText* comboDim);
        void setComboFecha(Gtk::ComboBoxText* comboFecha);
        virtual void setComboHecho(Gtk::ComboBoxText* comboHecho);
        void setEntryExtra(Gtk::Entry* entryExtra);
        void setBotonEliminar(Gtk::ToolButton* botonEliminar);
        virtual void especializarVista() = 0;

        virtual void on_combo_dimension_changed() = 0;
        void on_boton_eliminar_clicked();
};

#endif  // FILTRADOR_CONFIG_MODELO_H
