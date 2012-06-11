#ifndef FILTRADOR_FILTRO_HECHO_H
#define FILTRADOR_FILTRO_HECHO_H

#include "FiltradorFiltro.h"

class FiltradorFiltroHecho : public FiltradorFiltro {
    public:
        FiltradorFiltroHecho(const Glib::ustring& filtro,
                             const Glib::ustring& valor);
        ~FiltradorFiltroHecho();
    private:
        bool esValido(const Glib::ustring& valor);
};

#endif  // FILTRADOR_FILTRO_HECHO_H

