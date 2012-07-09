#ifndef FILTRO_CONFIG_MODELO_H
#define FILTRO_CONFIG_MODELO_H

#include "FiltradorConfigModelo.h"

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
        void on_combo_dimension_changed();
        void on_entry_changed();
};

#endif  // FILTRO_CONFIG_MODELO_H