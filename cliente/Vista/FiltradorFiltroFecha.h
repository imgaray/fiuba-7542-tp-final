#ifndef FILTRADOR_FILTRO_FECHA_H
#define FILTRADOR_FILTRO_FECHA_H

#include "FiltradorFiltro.h"

class FiltradorFiltroFecha : public FiltradorFiltro {
    public:
        FiltradorFiltroFecha(const Glib::ustring& fecha,
                             const Glib::ustring& valorCombo,
                             const std::string& valorEntrada);
        ~FiltradorFiltroFecha();

        Consulta& filtrar(Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
        int i;  // iésimo valor del combobox posible
};

#endif  // FILTRADOR_FILTRO_FECHA_H
