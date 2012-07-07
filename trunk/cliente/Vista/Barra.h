#ifndef BARRA_H
#define BARRA_H

#include "Area.h"

class Barra : public Area {
    public:
        Barra(const Hecho& dato, double maximo, unsigned i, double offset,
              double separacion, double ancho);
        ~Barra();

        void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);
        bool fueClickeada(double x, double y);
        double getAvance();
    private:
        double sep;
        double ancho;
        double hasta;
        double x0;
        double y0;
};

#endif  // BARRA_H

