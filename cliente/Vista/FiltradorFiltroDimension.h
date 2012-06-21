#ifndef FILTRADOR_FILTRO_DIMENSION_H
#define FILTRADOR_FILTRO_DIMENSION_H

#include "FiltradorFiltro.h"
#include <gtkmm/separator.h>

class FiltradorFiltroDimension : public FiltradorFiltro {
    public:
        FiltradorFiltroDimension(const Glib::ustring& filtro,
                                 const Glib::ustring& valor);
        ~FiltradorFiltroDimension();

        (Consulta& c);
};

#endif  // FILTRADOR_FILTRO_DIMENSION_H
