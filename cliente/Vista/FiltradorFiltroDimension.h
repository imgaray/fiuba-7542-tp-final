#ifndef FILTRADOR_FILTRO_DIMENSION_H
#define FILTRADOR_FILTRO_DIMENSION_H

#include "FiltradorFiltro.h"
#include <gtkmm/separator.h>

/** @class FiltradorFiltroDimension
 * Filtro de comportamiento "básico", es decir, no es hecho ni fecha.
 */
class FiltradorFiltroDimension : public FiltradorFiltro {
    public:
        FiltradorFiltroDimension(const Glib::ustring& filtro,
                                 const Glib::ustring& valor);
        ~FiltradorFiltroDimension();

        void filtrar(Consulta& c);
};

#endif  // FILTRADOR_FILTRO_DIMENSION_H
