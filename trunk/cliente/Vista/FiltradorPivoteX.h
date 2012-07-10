#ifndef FILTRADOR_PIVOTE_X_H
#define FILTRADOR_PIVOTE_X_H

#include "Filtrador.h"
#include <gtkmm/separator.h>

/** @class FiltradorPivoteX
 * Filtrador concretado en un elemento de X de la tabla pivote.
 */
class FiltradorPivoteX : public Filtrador {
    public:
        /**
         * Constructor.
         * @param valor nombre del campo
         */
        FiltradorPivoteX(const Glib::ustring& valor);
        /**
         * Destructor.
         */
        ~FiltradorPivoteX();

        /**
         * Agrega un elemento al grupo X de la consulta de tabla pivote.
         * @param c consulta
         */
        void filtrar(Consulta& c);
    private:
        Gtk::Label valor;
};

#endif  // FILTRADOR_PIVOTE_X_H

