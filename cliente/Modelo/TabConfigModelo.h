#ifndef TAB_CONFIG_MODELO_H
#define TAB_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>
#include "ConfigModelo.h"

#define NOMBRE_TAB_POR_DEFECTO "Nueva pestaña"
#define MAX_GRILLA 9

class AdminConfigObjManager;
class FiltradorConfigManager;
class PanelConfigModelo;
class Tab;

/** @class TabConfigModelo
 * Clase concreta que modela la configuración de una pestaña.
 *
 * Un método importante que posee es Tab* concretarConfig(), dado que
 * mediante este se generan los entes mismos de la aplicación, capaces
 * de componerse por paneles consultantes, difundir navegabilidad, etc.
 */
class TabConfigModelo : public ConfigModelo {
    public:
        /**
         * Constructor.
         */
		TabConfigModelo();
        /**
         * Destructor.
         */
        ~TabConfigModelo();

        /**
         * Setter para los elementos de la vista que refieren al manejo de los
         * paneles a configurar. Conecta también señales.
         */
        void setObjManagerPanel(Gtk::ComboBoxText* cbtext,
                                Gtk::Entry* pEntryPanelLabel,
                                Gtk::Button* pAceptar,
                                Gtk::Button* pGuardarCambios,
                                Gtk::Button* pEliminar
                                );

        /**
         * Setter para los elementos de la vista que refieren a la
         * configuración del tamaño de la grilla.
         */
        void setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                  Gtk::SpinButton* pCols);

        /**
         * Setter para los elementos de la vista que refieren a la
         * configuración de los inputs.
         */
        void setInputsHandlers(const filtradoresHandlers& handlers);

        sigc::signal< void, PanelConfigModelo* > signal_panel_model_changed();

        PanelConfigModelo* getModeloPanel() const;

        /**
         * En base a lo configurado, retorna una instancia concreta de Tab
         * @return manage(Tab* )
         */
        Tab* concretarConfig();

        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    private:
        /* modelo mismo */
        int filas, cols;
        int min_fila, min_col;
        PanelConfigModelo* ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];
        FiltradorConfigManager* inputsManager;


        /* vista */
            /* conexiones a las señales */
            sigc::connection connectionSpinButtonFilas, connectionSpinButtonCols;
            void desconectarDeHijo();

            /* signal handlers */

            /**
             * Signal handler para el cambio de la cantidad de filas de la
             * grilla.
             *
             * Si es mayora min_fila, lo setea en el atributo filas.
             */
            void on_spinbutton_filas_value_changed();


            /**
             * Signal handler para el cambio de la cantidad de columnas de la
             * grilla.
             *
             * Si es mayora min_col, lo setea en el atributo cols.
             */
            void on_spinbutton_cols_value_changed();

            /* referencias */
            Gtk::SpinButton* pSpinButtonFilas;
            Gtk::SpinButton* pSpinButtonCols;

        /* cosas de paneles */
            /* señales */
            sigc::signal< void, PanelConfigModelo* > _signal_panel_model_changed;

            /* conexiones */
            sigc::connection connectionPanelPosicion;

            /* signal handlers */

            /**
             * Signal handler para la solicitud de validez de la posición
             * puesta en sus Gtk::SpinButtons.
             *
             * Si están libres, le setea al panel la posición como válida.
             * @param pPanel    panel solicitante
             * @param desdeFila límite superior que pretende en la grilla
             * @param hastaFila límite inferior que pretende en la grilla
             * @param desdeCol  límite izquierdo que pretende en la grilla
             * @param hastaCol  límite derecho que pretende en la grilla
             */
            void on_panel_solicita_validacion(PanelConfigModelo* pPanel,
                                              int desdeFila,
                                              int hastaFila,
                                              int desdeCol,
                                              int hastaCol);

            /* modelo */
            AdminConfigObjManager* panelManager;
            PanelConfigModelo* pModeloPanel;
            void ocuparGrilla(PanelConfigModelo* pModelo);
            void desocuparGrilla(PanelConfigModelo* pModelo);

            /**
             * Signal handler para la señal
             * AdminConfigObjManager::_signal_model_changed.
             *
             * Fija el modelo nuevo como actual y emite
             * _signal_panel_model_changed
             * @param m modelo nuevo
             */
            void on_panel_model_changed(ConfigModelo* m);

            /**
             * Signal handler para la señal
             * AdminConfigObjManager::_signal_model_saved.
             *
             * Actualiza la posición en la grilla, que se supone validada.
             * @param m modelo nuevo
             */
            void on_panel_model_saved(ConfigModelo* m);

            /**
             * Signal handler para la señal
             * AdminConfigObjManager::_signal_model_deleted.
             *
             * Desocupa la grilla de este modelo.
             * @param m modelo nuevo
             */
            void on_panel_model_deleted(ConfigModelo* m);
};

#endif  // TAB_CONFIG_MODELO_H

