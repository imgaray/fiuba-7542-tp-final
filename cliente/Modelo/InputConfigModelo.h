#ifndef INPUT_CONFIG_MODELO_H
#define INPUT_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"


class InputConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        InputConfigModelo(unsigned ID,
                          const std::list< std::string >& _camposDisponibles);
        ~InputConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // INPUT_CONFIG_MODELO_H


