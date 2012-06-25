#ifndef PANEL_CONFIG_MODELO_H
#define PANEL_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include "ConfigModelo.h"

#define NOMBRE_PANEL_POR_DEFECTO "Nuevo panel"

class PanelConfigModelo : public ConfigModelo {
    public:
        PanelConfigModelo();
        ~PanelConfigModelo();

    private:
        /** modelo mismo */


        /** conexiones a las señales de la vista */

        void desconectarDeHijo();

        /** signal handlers */


        /** referencias a la vista */

};

#endif  // PANEL_CONFIG_MODELO_H

