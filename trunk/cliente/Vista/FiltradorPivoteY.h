#ifndef FILTRADOR_PIVOTE_Y_H
#define FILTRADOR_PIVOTE_Y_H

#include "Filtrador.h"
#include <gtkmm/separator.h>

/** @class FiltradorPivoteY
 * Filtrador concretado en un elemento de Y de la tabla pivote.
 */
class FiltradorPivoteY : public Filtrador {
    public:
        FiltradorPivoteY(const Glib::ustring& valor);
        ~FiltradorPivoteY();

        void filtrar(Consulta& c);
    private:
        Gtk::Label valor;
};

#endif  // FILTRADOR_PIVOTE_Y_H


