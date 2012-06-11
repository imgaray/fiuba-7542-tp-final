#ifndef FILTRADOR_FILTRO_H
#define FILTRADOR_FILTRO_H

#include "Filtrador.h"
#include <gtkmm/separator.h>

class FiltradorFiltro : public Filtrador {
    public:
        FiltradorFiltro(const Glib::ustring& filtro,
                        const Glib::ustring& valor);
        virtual ~FiltradorFiltro();
    protected:
        void setValor(const Glib::ustring& valor);
    private:
        virtual bool esValido(const Glib::ustring& valor) = 0;
        Gtk::VSeparator sep;
        Gtk::Label valor;
};

#endif  // FILTRADOR_FILTRO_H
