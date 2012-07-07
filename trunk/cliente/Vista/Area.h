#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>
#include "Hecho.h"

#define MAX_VALORES 15

class Area {
    public:
        Area(const Hecho& dato, double maximo, unsigned i, double offset);
        ~Area();

        const Glib::ustring& getEtiqueta() const;
        virtual const double* getColor() const;

        virtual void dibujar(Cairo::RefPtr< Cairo::Context >& ctx) = 0;
        virtual bool fueClickeada(double x, double y) = 0;

        virtual double getAvance() = 0;

        void setSeleccionada(bool selec);
    protected:
        /** @todo quizás con una referencia al hecho baste, hasta podría ser
         * más conveniente si está directamente conectado con las consultas
         */
        Hecho dato;
        double max;
        double color[4];
        double offset;

        void set_line_width(Cairo::RefPtr< Cairo::Context >& ctx);
    private:
        static double colores[MAX_VALORES][4];
        double lineWidth;
};

#endif  // AREA_H
