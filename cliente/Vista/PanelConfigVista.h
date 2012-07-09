#ifndef PANEL_CONFIG_VISTA_H
#define PANEL_CONFIG_VISTA_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/expander.h>
#include "Buildable.h"

class PanelConfigModelo;

class PanelConfigVista : public Gtk::VBox, public Buildable  {
    public:
        /**
         * @brief constructor requerido para construir con Gtk::Builder
         * @param cobject puntero al tipo base
         * @param builder referencia a la instancia que lo construye
         */
        PanelConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& builder);
        ~PanelConfigVista();

        void setModelo(PanelConfigModelo* pModeloNuevo);
    private:
        PanelConfigModelo* pModelo;

        Gtk::Label* pLabelPosicion;
        Gtk::SpinButton* pSpinbuttonDesdeFila;
        Gtk::SpinButton* pSpinbuttonHastaFila;
        Gtk::SpinButton* pSpinbuttonDesdeCol;
        Gtk::SpinButton* pSpinbuttonHastaCol;
        Gtk::ComboBoxText comboTipoGrafico;
        Gtk::Expander* pExpanderXPivote;
        Gtk::Expander* pExpanderYPivote;

        // filtradores
        Gtk::VBox* pFiltros;
        Gtk::ToolButton* pBotonAgregarFiltro;
        Gtk::VBox* pInputs;
        Gtk::ToolButton* pBotonAgregarInput;
        Gtk::VBox* pPivoteXs;
        Gtk::ToolButton* pBotonAgregarPivoteX;
        Gtk::VBox* pPivoteYs;
        Gtk::ToolButton* pBotonAgregarPivoteY;
        Gtk::VBox* pResultados;
        Gtk::ToolButton* pBotonAgregarResultado;

        void initFiltradores(const Glib::ustring& nombreFilt,
                             Gtk::VBox*& pFilt,
                             const Glib::ustring& nombreBoton,
                             Gtk::ToolButton*& pAgregar);
};

#endif  // PANEL_CONFIG_VISTA_H

