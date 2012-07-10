#ifndef PANEL_CONFIG_MODELO_H
#define PANEL_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/expander.h>
#include "ConfigModelo.h"

#define NOMBRE_PANEL_POR_DEFECTO "Nuevo panel"

class FiltradorConfigManager;
class Panel;
class FiltradoresPanel;

/** @class PanelConfigModelo
 * Clase concreta que modela la configuración de un panel.
 *
 * Un método importante que posee es Panel* concretarConfig(), dado que
 * mediante este se generan los entes mismos de la aplicación, capaces
 * de mostrar los filtradores aplicados, hacer consultas y representar
 * gráficamente respuestas.
 */
class PanelConfigModelo : public ConfigModelo {
    public:
        PanelConfigModelo();
        ~PanelConfigModelo();

        void setLabelPosicion(Gtk::Label* pLabel);
        void setSpinbuttonsPosicion(Gtk::SpinButton* pSpinbuttondesdeFila,
                                    Gtk::SpinButton* pSpinbuttonhastaFila,
                                    Gtk::SpinButton* pSpinbuttonDesdeCol,
                                    Gtk::SpinButton* pSpinbuttonHastaCol);
        void setPosicionNuevaComoValida(bool valida = true);
        void setComboboxTipoGrafico(Gtk::ComboBoxText* pCombo);
        void setExpandersPivote(Gtk::Expander* pXPivote, Gtk::Expander* pYPivote);

        void setFiltrosHandlers(const filtradoresHandlers& handlers);
        void setInputsHandlers(const filtradoresHandlers& handlers);
        void setPivoteXsHandlers(const filtradoresHandlers& handlers);
        void setPivoteYsHandlers(const filtradoresHandlers& handlers);
        void setResultadosHandlers(const filtradoresHandlers& handlers);

        void getPosicion(int& desdeFila, int& hastaFila,
                         int& desdeCol, int& hastaCol);

        sigc::signal< void, PanelConfigModelo*, int, int, int, int > signal_posicion_changed();

        Panel* concretarConfig(FiltradoresPanel* filtPanel);

        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

    private:
        /* modelo mismo */
        int desdeFila, hastaFila;
        int desdeCol, hastaCol;
        bool posicionValida, posicionesDeserializadas;
        FiltradorConfigManager* filtrosManager;
        FiltradorConfigManager* inputsManager;
        FiltradorConfigManager* pivoteXsManager;
        FiltradorConfigManager* pivoteYsManager;
        FiltradorConfigManager* resutadosManager;

        int indice_tipoGrafico;
        static Glib::ustring tiposGrafico[];
        /* señales propias */
        sigc::signal< void, PanelConfigModelo*, int, int, int, int > _signal_posicion_changed;

        void desconectarDeHijo();
        /* conexiones a las señales de la vista */
        sigc::connection connectionLabelPosicion;
        sigc::connection connectionSpinButtonDesdeFila;
        sigc::connection connectionSpinButtonHastaFila;
        sigc::connection connectionSpinButtonDesdeCol;
        sigc::connection connectionSpinButtonHastaCol;
        sigc::connection connectionComboboxTipoGrafico;
        void bloquearConnectionPosicion();
        void desbloquearConnectionPosicion();


        /* signal handlers*/

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de campo.
         *
         * Consigue de los Gtk::SpinButtons los cuatro nuevos valores que
         * definen su posición. Los arregla dentro de lo que puede ver el
         * método, por ejemplo, si la selección del admin genera:
         * @code{.cpp}
         * desdeFila = 1;
         * hastaFila = 1;
         * @endcode
         * entonces se aumenta en uno @code{.cpp} hastaFila @endcode
         * Finalmente, emite la señal _signal_posicion_changed, solicitando
         * validación por parte de la grilla.
         *
         */
        void on_spinbuttons_posicion_changed();

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de tipo de gráfico.
         *
         * Almacena en indice_tipoGrafico el valor de la selección actual y
         * verifica si es o no PIVOTE para mostrar o no sus opciones
         * específicas.
         */
        void on_combobox_tipo_grafico_changed();



        /* referencias a la vista */
        Gtk::Label* pLabelPosicion;
        Gtk::SpinButton* pSpinButtonDesdeFila;
        Gtk::SpinButton* pSpinButtonHastaFila;
        Gtk::SpinButton* pSpinButtonDesdeCol;
        Gtk::SpinButton* pSpinButtonHastaCol;
        Gtk::ComboBoxText* pComboBoxTextTipoGrafico;
        Gtk::Expander* pExpanderXPivote;
        Gtk::Expander* pExpanderYPivote;
};

#endif  // PANEL_CONFIG_MODELO_H

