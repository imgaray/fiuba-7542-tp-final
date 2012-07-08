#ifndef PORCION_CIRCULAR_H
#define PORCION_CIRCULAR_H

#include "Area.h"

class PorcionCircular : public Area {
    public:
        PorcionCircular(const Hecho& dato, double maximo, unsigned i,
                        double offset,
                        double x0, double y0, double radio);
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
