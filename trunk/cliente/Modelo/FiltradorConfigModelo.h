#ifndef FILTRADOR_CONFIG_MODELO_H
#define FILTRADOR_CONFIG_MODELO_H

#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/toolbutton.h>

#include "Serializable.h"

class FiltradoresTab;
class FiltradoresPanel;

class FiltradorConfigModelo : public Serializable {
    public:
        FiltradorConfigModelo(unsigned ID);
        ~FiltradorConfigModelo();

        void setVista(Gtk::ComboBoxText* comboDimension,
                      Gtk::ComboBoxText* comboFecha,
                      Gtk::ComboBoxText* comboHecho,
                      Gtk::Entry* entryExtra,
                      Gtk::ToolButton* botonEliminar);

        unsigned getID() const;

        sigc::signal< void, unsigned > signal_delete_filtrador();

        virtual void setFiltradorEn(FiltradoresTab* filtTab) = 0;
        virtual void setFiltradorEn(FiltradoresPanel* filtPanel) = 0;


        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    protected:
        Gtk::ComboBoxText* comboDimension;
        Gtk::ComboBoxText* comboFecha;
        Gtk::ComboBoxText* comboHecho;
        Gtk::Entry* entryExtra;

        Glib::ustring campoSelecc;
        Glib::ustring _valorCampo;
        Glib::ustring _campoAux;
    private:
        Gtk::ToolButton* botonEliminar;

        unsigned ID;

        sigc::signal< void, unsigned > _signal_delete_filtrador;

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
