#ifndef PANEL_CONFIG_MODELO_H
#define PANEL_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include "ConfigModelo.h"

#define NOMBRE_PANEL_POR_DEFECTO "Nuevo panel"

class PanelConfigModelo : public ConfigModelo {
    public:
        PanelConfigModelo();
        ~PanelConfigModelo();

        void setSpinbuttonsPosicion(Gtk::SpinButton* pSpinbuttondesdeFila,
                                    Gtk::SpinButton* pSpinbuttonhastaFila,
                                    Gtk::SpinButton* pSpinbuttonDesdeCol,
                                    Gtk::SpinButton* pSpinbuttonHastaCol);

    private:
        /** modelo mismo */
        unsigned desdeFila, hastaFila;
        unsigned desdeCol, hastaCol;

        /** conexiones a las señales de la vista */

        void desconectarDeHijo();

        /** signal handlers */


        /** referencias a la vista */
        Gtk::SpinButton* pSpinButtonDesdeFila;
        Gtk::SpinButton* pSpinButtonHastaFila;
        Gtk::SpinButton* pSpinButtonDesdeCol;
        Gtk::SpinButton* pSpinButtonHastaCol;
};

#endif  // PANEL_CONFIG_MODELO_H

