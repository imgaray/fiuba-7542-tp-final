#ifndef BARRA_H
#define BARRA_H

#include "Area.h"

/** @class Barra
 * Clase concreta que representa una barra de un gráfico de barras.
 */
class Barra : public Area {
    public:
        /**
         * Constructor.
         */
        Barra(const Hecho& dato, double maximo, unsigned i, double offset,
              double separacion, double ancho);
        /**
         * Destructor.
         */
        ~Barra();

        void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);
        bool fueClickeada(double x, double y);
        double getAvance();

        std::string getInfo();
    private:
        double sep;
        double ancho;
        double hasta;
        double x0;
        double y0;
};

#endif  // BARRA_H

