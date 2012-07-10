#ifndef RESULTADO_CONFIG_MODELO_H
#define RESULTADO_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

/** @class ResultadoConfigModelo
 * Clase que modela la configuración de un resultado para una consulta.
 * Esto es selección de campo, y si es un hecho, selección de agregación.
 */
class ResultadoConfigModelo : public FiltradorConfigModelo {
    public:
        ResultadoConfigModelo(unsigned ID,
                        const std::list< std::string >& _camposDisponibles);
        ~ResultadoConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);

    protected:
        virtual void completarAtributos();

    private:
        void especializarVista();
        void setComboHecho(Gtk::ComboBoxText* comboHecho);

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de campo.
         *
         * Emite la señal _signal_campo_changed con el campo anteriormente
         * seleccionado y el nuevo. Según el campo nuevo, se muestran u
         * ocultan elementos de la vista.
         */
        void on_combo_dimension_changed();
};

#endif  // RESULTADO_CONFIG_MODELO_H

