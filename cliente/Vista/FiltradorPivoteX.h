#ifndef FILTRADOR_PIVOTE_X_H
#define FILTRADOR_PIVOTE_X_H

#include "Filtrador.h"
#include <gtkmm/separator.h>

class FiltradorPivoteX : public Filtrador {
    public:
        FiltradorPivoteX(const Glib::ustring& valor);
        ~FiltradorPivoteX();

        void filtrar(Consulta& c);
    private:
        Gtk::Label valor;
};

#endif  // FILTRADOR_PIVOTE_X_H

