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

/** @class FiltradorConfigVista
 * Representación visual de la configuración de un filtrador. Se construye
 * asociada a un modelo porque a diferencias de las otras vistas, es un
 * modelo por vista.
 *
 * Una vez relaciada al modelo, es controlada desde allí con lo cual, no tiene
 * ninguna otra particularidad.
 */
class FiltradorConfigVista : public Gtk::HBox {
    public:
        /**
         * Constructor.
         * @param pModelo el modelo asociado a esta vista
         */
        FiltradorConfigVista(FiltradorConfigModelo* pModelo);
        /**
         * Destructor.
         */
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
