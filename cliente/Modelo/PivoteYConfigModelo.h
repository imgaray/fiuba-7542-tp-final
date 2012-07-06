#ifndef PIVOTE_Y_CONFIG_MODELO_H
#define PIVOTE_Y_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"

class PivoteYConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        PivoteYConfigModelo(unsigned ID);
        ~PivoteYConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // PIVOTE_Y_CONFIG_MODELO_H
