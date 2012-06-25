#ifndef TAB_CONFIG_MODELO_H
#define TAB_CONFIG_MODELO_H

#include <gtkmm/spinbutton.h>
#include "ConfigModelo.h"

#define NOMBRE_TAB_POR_DEFECTO "Nueva pestaña"
#define MAX_GRILLA 99

class TabConfigModelo : public ConfigModelo {
    public:
        TabConfigModelo();
        ~TabConfigModelo();

        void setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                  Gtk::SpinButton* pCols);

    private:
        /** modelo mismo */
        unsigned filas, cols;
        unsigned min_fila, min_col;
        bool ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];

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

