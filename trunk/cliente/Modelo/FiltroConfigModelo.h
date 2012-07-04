#ifndef FILTRO_CONFIG_MODELO_H
#define FILTRO_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

class FiltroConfigModelo : public FiltradorConfigModelo {
    public:
        FiltroConfigModelo();
        ~FiltroConfigModelo();

    private:
        void especializarVista();
        void on_combo_dimension_changed();
};

#endif  // FILTRO_CONFIG_MODELO_H
