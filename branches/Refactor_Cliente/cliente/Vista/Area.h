#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>
#include "Hecho.h"

#ifndef MAX_VALORES
#define MAX_VALORES 9
#endif

#define DEFAULT_LINE_WIDTH  0.01
#define SELEC_LINE_WIDTH    1.5*DEFAULT_LINE_WIDTH

class Area {
    public:
        Area(const Hecho& dato, double maximo, unsigned i);
        ~Area();

        const Glib::ustring& getEtiqueta() const;
        virtual const double* getColor() const;

        virtual double dibujar(Cairo::RefPtr< Cairo::Context >& ctx,
                               double offset) = 0;
        virtual bool fueClickeada(double x, double y, double& offset) = 0;

        void setSeleccionada(bool selec);
    protected:
        /** @todo quizás con una referencia al hecho baste, hasta podría ser
         * más conveniente si está directamente conectado con las consultas
         */
        Hecho dato;
        double max;
        double color[4];
        bool seleccionada;
    private:
        static double colores[MAX_VALORES][4];
};

#endif  // AREA_H
