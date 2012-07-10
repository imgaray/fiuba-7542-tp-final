#ifndef FILTRO_CONFIG_MODELO_H
#define FILTRO_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

/** @class FiltroConfigModelo
 * Clase modelo de la configuración de un filtro para una consulta.
 * Selecciona campo. Si es fecha, puede seleccionar tipo de fecha (mes,
 * bimestre, año, etc.) e ingresar en una Gtk::Entry. Si es Hecho, selecciona
 * mayor, igual o menor y el valor en una Gtk::Entry. De otra manera, ingresa
 * en la Gtk::Entry el valor del filtro.
 */
class FiltroConfigModelo : public FiltradorConfigModelo {
    public:
        FiltroConfigModelo(unsigned ID,
                           const std::list< std::string >& camposDisponibles);
        ~FiltroConfigModelo();

        void setFiltradorEn(FiltradoresTab* filtTab);
        void setFiltradorEn(FiltradoresPanel* filtPanel);

    protected:

        virtual void completarAtributos();

    private:

        // mapa para poder recordar el ingreso en la Gtk::Entry del usuario
        // para cada campo del combobox
        std::map< Glib::ustring, Glib::ustring > entryPorCampo;
        void especializarVista();

        /**
         * Signal handler para el cambio en la opción seleccionada en el
         * combobox de campo.
         *
         * Emite la señal _signal_campo_changed con el campo anteriormente
         * seleccionado y el nuevo. Según el campo nuevo, se muestran u
         * ocultan elementos de la vista.
         */
        void on_combo_dimension_changed();

        /**
         * Signal handler para cada cambio en la entrada del admin.
         *
         * Almacena en _valorCampo el texto actual de la Gtk::Entry y en
         * el mapa entryPorCampo.
         */
        void on_entry_changed();
};

#endif  // FILTRO_CONFIG_MODELO_H
