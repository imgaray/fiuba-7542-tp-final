#ifndef INPUT_CONFIG_MODELO_H
#define INPUT_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"


class InputConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        InputConfigModelo(unsigned ID);
        ~InputConfigModelo();
        virtual NodoXml serializar();
        virtual void deserializar(const NodoXml& nodo);

};

#endif  // INPUT_CONFIG_MODELO_H


