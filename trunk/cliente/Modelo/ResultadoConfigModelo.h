#ifndef RESULTADO_CONFIG_MODELO_H
#define RESULTADO_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

class ResultadoConfigModelo : public FiltradorConfigModelo {
    public:
        ResultadoConfigModelo();
        ~ResultadoConfigModelo();

    private:
        void especializarVista();
        void setComboHecho(Gtk::ComboBoxText* comboHecho);
        void on_combo_dimension_changed();
};

#endif  // RESULTADO_CONFIG_MODELO_H

