#ifndef FILTRADOR_RESULTADO_H
#define FILTRADOR_RESULTADO_H

#include "Filtrador.h"
#include <gtkmm/label.h>

/** @class FiltradorResultado
 * Filtrador concretado en un resultado de la consulta. Como todavía varía
 * según el resultado sea un hecho, dimensión o fecha, sigue siendo una clase
 * abstracta.
 */
class FiltradorResultado : public Filtrador {
    public:
        FiltradorResultado(const Glib::ustring& resultado);
        virtual ~FiltradorResultado();

    protected:
        void setResultado(const Glib::ustring& resultado);
        Glib::ustring getResultado();
    private:
        Gtk::Label resultado;
};

#endif  // FILTRADOR_RESULTADO_H
