#ifndef PIVOTE_Y_CONFIG_MODELO_H
#define PIVOTE_Y_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"

/** @class PivoteYConfigModelo
 * Clase que modela la configuración de un elemento del grupo Y para una
 * consulta de tabla pivot.
 * Sólo selecciona el campo.
 */
class PivoteYConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        /**
         * Constructor.
         */
        PivoteYConfigModelo(unsigned ID,
                        const std::list< std::string >& _camposDisponibles);
        /**
         * Destructor.
         */
        ~PivoteYConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // PIVOTE_Y_CONFIG_MODELO_H

