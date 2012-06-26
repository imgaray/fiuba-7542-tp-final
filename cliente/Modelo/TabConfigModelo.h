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

class TabConfigModelo : public ConfigModelo {
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
        void setCheckButtonsFiltradores(const std::list< Gtk::CheckButton* >& filtradores);

        sigc::signal< void, PanelConfigModelo* > signal_panel_model_changed();

        PanelConfigModelo* getModeloPanel() const;

    private:
        /** modelo mismo */
        unsigned filas, cols;
        unsigned min_fila, min_col;
        std::list< bool > filtradoresTab;
        PanelConfigModelo* ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];

        /** vista */
            /** conexiones a las señales */
            sigc::connection connectionSpinButtonFilas, connectionSpinButtonCols;
            void desconectarDeHijo();

            /** signal handlers */
            void on_spinbutton_filas_value_changed();
            void on_spinbutton_cols_value_changed();
            void on_filtradores_toggled();

            /** referencias */
            Gtk::SpinButton* pSpinButtonFilas;
            Gtk::SpinButton* pSpinButtonCols;
            std::list< Gtk::CheckButton* > pCheckButtonsFiltradores;

        /** cosas de paneles */
            /** señales */
            sigc::signal< void, PanelConfigModelo* > _signal_panel_model_changed;

            /** conexiones */
            sigc::connection connectionPanelPosicion;
            std::list< sigc::connection > connectionCheckButtonsFiltradores;

            /** signal handlers */
            void on_panel_solicita_validacion(PanelConfigModelo* pPanel,
                                              int desdeFila,
                                              int hastaFila,
                                              int desdeCol,
                                              int hastaCol);

            /** modelo */
            AdminConfigObjManager* panelManager;
            PanelConfigModelo* pModeloPanel;
            void ocuparGrilla(PanelConfigModelo* pModelo);
            void desocuparGrilla(PanelConfigModelo* pModelo);
            void on_panel_model_changed(ConfigModelo* m);
            void on_panel_model_saved(ConfigModelo* m);
            void on_panel_model_deleted(ConfigModelo* m);


            void imprimirGrilla();
};

#endif  // TAB_CONFIG_MODELO_H

