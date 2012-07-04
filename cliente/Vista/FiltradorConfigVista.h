#ifndef FILTRADOR_CONFIG_VISTA_H
#define FILTRADOR_CONFIG_VISTA_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/stockid.h>

class FiltradorConfigModelo;

class FiltradorConfigVista : public Gtk::HBox {
    public:
        FiltradorConfigVista(FiltradorConfigModelo* pModelo);
        ~FiltradorConfigVista();

    private:
        Gtk::HBox filtConfigBox;
            Gtk::Label labelDim;
            Gtk::ComboBoxText comboDimension;
            Gtk::ComboBoxText comboFecha;
            Gtk::ComboBoxText comboHecho;
            Gtk::Entry entryExtra;
        Gtk::Toolbar tools;
            Gtk::StockID idBotonEliminar;
            Gtk::ToolButton botonEliminar;
};

#endif  // FILTRADOR_CONFIG_VISTA_H
