#ifndef PIVOTE_X_CONFIG_MODELO_H
#define PIVOTE_X_CONFIG_MODELO_H

#include "FiltradorSoloDimensionConfigModelo.h"

/** @class PivoteXConfigModelo
 * Clase que modela la configuración de un elemento del grupo X para una
 * consulta de tabla pivot.
 * Sólo selecciona el campo.
 */
class PivoteXConfigModelo : public FiltradorSoloDimensionConfigModelo {
    public:
        /**
         * Constructor.
         */
        PivoteXConfigModelo(unsigned ID,
                        const std::list< std::string >& _camposDisponibles);
        /**
         * Destructor.
         */
        ~PivoteXConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);
};

#endif  // PIVOTE_X_CONFIG_MODELO_H



