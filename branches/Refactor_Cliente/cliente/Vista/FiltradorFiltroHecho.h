#ifndef FILTRADOR_FILTRO_HECHO_H
#define FILTRADOR_FILTRO_HECHO_H

#include "FiltradorFiltro.h"

class FiltradorFiltroHecho : public FiltradorFiltro {
    public:
        FiltradorFiltroHecho(const Glib::ustring& hecho,
                             const Glib::ustring& valorCombo,
                             const std::string& valorEntrada);
        ~FiltradorFiltroHecho();

        Consulta& filtrar(Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
        int i;  // iésimo valor del combobox posible
        Glib::ustring valorHecho;
};

#endif  // FILTRADOR_FILTRO_HECHO_H

