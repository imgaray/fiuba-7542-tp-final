#ifndef FILTRADOR_FILTRO_FECHA_H
#define FILTRADOR_FILTRO_FECHA_H

#include "FiltradorFiltro.h"

/** @class FiltradorFiltroFecha
 * Filtro de tipo fecha.
 */
class FiltradorFiltroFecha : public FiltradorFiltro {
    public:
        /**
         * Constructor.
         * @param fecha nombre del campo fecha
         * @param valorCombo tipo de filtrado de la fecha ("Año", "Bimestre",
         * etc.)
         * @param valorEntrada valor del filtro ("2012", "2-2012", etc.)
         */
        FiltradorFiltroFecha(const Glib::ustring& fecha,
                             const Glib::ustring& valorCombo,
                             const std::string& valorEntrada);
        /**
         * Destructor.
         */
        ~FiltradorFiltroFecha();

        /**
         * Agrega el filtro a la consulta.
         * @param c consulta
         */
        void filtrar(Consulta& c);

    private:
        Glib::ustring valorCombo;
        Glib::ustring valorEntrada;
        int i;  // iésimo valor del combobox posible
        Fecha f;
};

#endif  // FILTRADOR_FILTRO_FECHA_H
