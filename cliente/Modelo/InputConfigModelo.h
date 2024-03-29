#ifndef INPUT_CONFIG_MODELO_H
#define INPUT_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"

/** @class InputConfigModelo
 * Clase que modela la configuración de un input para una consulta.
 * Sólo selecciona el campo.
 */
class InputConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        /**
         * Constructor.
         */
        InputConfigModelo(unsigned ID,
                          const std::list< std::string >& _camposDisponibles);
        /**
         * Destructor.
         */
        ~InputConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // INPUT_CONFIG_MODELO_H


