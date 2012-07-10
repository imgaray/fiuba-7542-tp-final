#ifndef FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H
#define FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

/** @class FiltradorSoloDimensionConfigModelo
 * Clase base para filtradores que sólo tienen una string útil (la que indica
 * qué campo se seleccionó) y se comportan igual en todos los aspectos salvo
 * al momento de construir la consulta.
 */
class FiltradorSoloDimensionConfigModelo : public FiltradorConfigModelo {
    public:
        FiltradorSoloDimensionConfigModelo(unsigned ID,
                        const std::list< std::string >& _camposDisponibles);
        ~FiltradorSoloDimensionConfigModelo();

    protected:
        virtual void completarAtributos();

    private:
        void especializarVista();

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de campo.
         *
         * Emite la señal _signal_campo_changed con el campo anteriormente
         * seleccionado y el nuevo.
         */
        void on_combo_dimension_changed();
};

#endif  // FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H

