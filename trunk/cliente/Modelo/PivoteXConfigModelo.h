#ifndef PIVOTE_X_CONFIG_MODELO_H
#define PIVOTE_X_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"

class PivoteXConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        PivoteXConfigModelo(unsigned ID);
        ~PivoteXConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // PIVOTE_X_CONFIG_MODELO_H



