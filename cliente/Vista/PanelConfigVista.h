#ifndef PANEL_CONFIG_VISTA_H
#define PANEL_CONFIG_VISTA_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include "Buildable.h"

class PanelConfigModelo;

class PanelConfigVista : public Gtk::VBox, public Buildable  {
    public:
        PanelConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~PanelConfigVista();

        void setModelo(PanelConfigModelo* pModeloNuevo);
    private:
        PanelConfigModelo* pModelo;

        Gtk::Entry* pEntryPanelLabel;
        Gtk::Label* pLabelPosicion;
        Gtk::SpinButton* pSpinbuttonDesdeFila;
        Gtk::SpinButton* pSpinbuttonHastaFila;
        Gtk::SpinButton* pSpinbuttonDesdeCol;
        Gtk::SpinButton* pSpinbuttonHastaCol;
        Gtk::ComboBoxText comboTipoGrafico;
};

#endif  // PANEL_CONFIG_VISTA_H

