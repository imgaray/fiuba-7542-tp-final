#ifndef FILTRADOR_FILTRO_FECHA_H
#define FILTRADOR_FILTRO_FECHA_H

#include "FiltradorFiltro.h"

class FiltradorFiltroFecha : public FiltradorFiltro {
    public:
        FiltradorFiltroFecha(const Glib::ustring& filtro,
                             const Glib::ustring& valor);
        ~FiltradorFiltroFecha();
    private:
        bool esValido(const Glib::ustring& valor);
};

#endif  // FILTRADOR_FILTRO_FECHA_H
