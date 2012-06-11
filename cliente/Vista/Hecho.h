#ifndef HECHO_H
#define HECHO_H

#include <glibmm/ustring.h>

class Hecho {
    public:
        Hecho(const Hecho& original);
        Hecho(const Glib::ustring& etiqueta, double valor);
        ~Hecho();

        Hecho& operator=(const Hecho& original);

        const Glib::ustring& getEtiqueta() const;
        double getValor() const;
    private:
        Glib::ustring etiqueta;
        double valor;
};

#endif  // HECHO_H
