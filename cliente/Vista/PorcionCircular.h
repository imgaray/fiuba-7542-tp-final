#ifndef PORCION_CIRCULAR_H
#define PORCION_CIRCULAR_H

#include "Area.h"

/** @class PorcionCircular
 * Clase concreta que representa una porción circular de un gráfico de torta.
 */
class PorcionCircular : public Area {
    public:
        /**
         * Constructor.
         * @param dato aquello que representará la porción
         * @param maximo el valor máximo encontrado
         * @param i número de porción (esto es méramente por el color)
         * @param offset desplazamiento de la porción
         * @param x0 centro del círculo
         * @param y0 centro del círculo
         * @param radio radio del círculo
         */
        PorcionCircular(const Hecho& dato, double maximo, unsigned i,
                        double offset,
                        double x0, double y0, double radio);
        /**
         * Destructor.
         */
        ~PorcionCircular();

        void dibujar(Cairo::RefPtr< Cairo::Context >& ctx);
        bool fueClickeada(double x, double y);
        double getAvance();
        std::string getInfo();
    private:
        double x0;
        double y0;
        double r;
        double valor;
};

#endif  // PORCION_CIRCULAR_H
