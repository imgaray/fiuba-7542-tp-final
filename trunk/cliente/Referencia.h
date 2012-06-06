#ifndef REFERENCIA_H
#define REFERENCIA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>

class Area;

class Referencia {
    public:
        Referencia(const Area& referente);
        ~Referencia();

        double dibujar(Cairo::RefPtr< Cairo::Context >& ctx, double offset);
    private:
        double color[4];
        Glib::ustring etiqueta;
        static double anchoCuadradito;
};

#endif  // REFERENCIA_H
