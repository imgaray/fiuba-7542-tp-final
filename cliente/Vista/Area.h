#ifndef AREA_H
#define AREA_H

#include <cairomm/context.h>
#include <glibmm/ustring.h>
#include "Hecho.h"

/** @class Area
 * Clase abstracta que comprende comportamiento común a toda área de un
 * gŕafico, como la capacidad de responder si un click del mouse cayó sobre
 * ella, retornar una string informativa y, el más importante, dibujarse.
 */
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

        virtual std::string getInfo() = 0;
    protected:
        Hecho dato;
        double max;
        double color[4];
        double offset;

        void set_line_width(Cairo::RefPtr< Cairo::Context >& ctx);
    private:
        static double colores[][4];
        double lineWidth;
};

#endif  // AREA_H
