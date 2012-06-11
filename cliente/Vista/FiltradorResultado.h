#ifndef FILTRADOR_RESULTADO_H
#define FILTRADOR_RESULTADO_H

#include "Filtrador.h"
#include <gtkmm/label.h>

class FiltradorResultado : public Filtrador {
    public:
        FiltradorResultado(const Glib::ustring& resultado);
        virtual ~FiltradorResultado();
    protected:
        void setResultado(const Glib::ustring& resultado);
    private:
        Gtk::Label resultado;
};

#endif  // FILTRADOR_RESULTADO_H
