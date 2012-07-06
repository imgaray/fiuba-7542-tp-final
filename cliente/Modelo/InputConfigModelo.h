#ifndef INPUT_CONFIG_MODELO_H
#define INPUT_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"


class InputConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        InputConfigModelo(unsigned ID);
        ~InputConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // INPUT_CONFIG_MODELO_H


