#ifndef TAB_CONFIG_MODELO_H
#define TAB_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include "ConfigModelo.h"

#define NOMBRE_TAB_POR_DEFECTO "Nueva pestaña"
#define MAX_GRILLA 99

class AdminConfigObjManager;
class PanelConfigModelo;

class TabConfigModelo : public ConfigModelo, public sigc::trackable {
    public:
        TabConfigModelo();
        ~TabConfigModelo();

        void setObjManagerPanel(Gtk::ComboBoxText* cbtext,
                                Gtk::Button* pAceptar,
                                Gtk::Button* pGuardarCambios,
                                Gtk::Button* pEliminar
                                );
        void setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                  Gtk::SpinButton* pCols);

        sigc::signal< void, PanelConfigModelo* > signal_panel_model_changed();

        PanelConfigModelo* getModeloPanel() const;

    private:
        /** modelo mismo */
        unsigned filas, cols;
        unsigned min_fila, min_col;
        bool ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];

        /** paneles */
        sigc::signal< void, PanelConfigModelo* > _signal_panel_model_changed;
        AdminConfigObjManager* panelManager;
        PanelConfigModelo* pModeloPanel;
        void on_panel_model_changed(ConfigModelo* m);

        /** conexiones a las señales de la vista */
        sigc::connection connectionSpinButtonFilas, connectionSpinButtonCols;
        void desconectarDeHijo();

        /** signal handlers */
        void on_spinbutton_filas_value_changed();
        void on_spinbutton_cols_value_changed();

        /** referencias a la vista */
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;
};

#endif  // TAB_CONFIG_MODELO_H

