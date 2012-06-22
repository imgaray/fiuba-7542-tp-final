#include "Area.h"
#include "Hecho.h"
#include <iostream>
double Area::colores[MAX_VALORES][4] = {
    {0.77, 0.2, 0.4, 1.0}, {0.4, 0.77, 0.2, 1.0}, {0.4, 0.3, 0.77, 1.0},
    {0.7, 0.3, 0.77, 1.0}, {0.1, 0.7, 0.77, 1.0}, {0.4, 0.9, 0.77, 1.0},
    {0.4, 0.67, 0.9, 1.0}, {0.9, 0.67, 0.4, 1.0}, {0.9, 0.4, 0.67, 1.0},
    {0.22, 0.2, 0.4, 1.0}, {0.4, 0.22, 0.2, 1.0}, {0.2, 0.4, 0.22, 1.0},
    {0.99, 0.3, 0.9, 1.0}, {0.1, 0.9, 0.99, 1.0}, {0.4, 0.9, 0.99, 1.0},
};

Area::Area(const Hecho& _dato, double maximo, unsigned i) : dato(_dato) {
    seleccionada = false;
    max = maximo;
    unsigned color_i = i % MAX_VALORES;
    for (unsigned j = 0; j < 4; ++j)
        color[j] = colores[color_i][j];
}

Area::~Area() {}

const Glib::ustring& Area::getEtiqueta() const {
    return dato.getEtiqueta();
}

const double* Area::getColor() const {
    return color;
}

void Area::setSeleccionada(bool selec) {
    seleccionada = selec;
}
