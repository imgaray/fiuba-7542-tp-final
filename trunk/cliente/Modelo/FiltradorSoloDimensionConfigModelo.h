#ifndef FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H
#define FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

class FiltradorSoloDimensionConfigModelo : public FiltradorConfigModelo {
    public:
        FiltradorSoloDimensionConfigModelo(unsigned ID,
                        const std::list< std::string >& _camposDisponibles);
        ~FiltradorSoloDimensionConfigModelo();

    protected:
        virtual void completarAtributos();

    private:
        void especializarVista();
        void on_combo_dimension_changed();
};

#endif  // FILTRADOR_SOLO_DIMENSION_CONFIG_MODELO_H
