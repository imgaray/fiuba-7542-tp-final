#include "FiltradorResultadoHecho.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"

#define CANT_AGREG 6
Glib::ustring FiltradorResultadoHecho::agregPosibles[CANT_AGREG] = {
    "NADA", "SUM", "MAX", "MIN", "PROM", "CONT" };

FiltradorResultadoHecho::FiltradorResultadoHecho(const Glib::ustring& _hecho,
    const Glib::ustring& _agregacion)
    : FiltradorResultado(STR_NULA), hecho(_hecho) {
    bool existeAgregacion = false;
    i = 0;
    while (!existeAgregacion && i < CANT_AGREG)
        existeAgregacion = _agregacion == agregPosibles[i++];

    if (!existeAgregacion) {
        std::string msj = "No pertenece al conjunto de agregaciones posibles: ";
        msj += _agregacion.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }


    Glib::ustring label = agregPosibles[--i];
    label += "(";
    label += hecho;
    label += ")";
    setResultado(label);

    switch (i) {
        case 0:  agregacion = NADA; break;
        case 1:  agregacion = SUM;  break;
        case 2:  agregacion = MAX;  break;
        case 3:  agregacion = MIN;  break;
        case 4:  agregacion = PROM; break;
        case 5:  agregacion = CONT; break;
        default: agregacion = NADA; break;
    }
}

FiltradorResultadoHecho::~FiltradorResultadoHecho() {}

Consulta& FiltradorResultadoHecho::filtrar(Consulta& c) {
    c.defininirAgregacion(agregacion, hecho);
    return c;
}

Glib::ustring FiltradorResultadoHecho::pertenece(const Glib::ustring& valor) {
    std::cout << "@todo Glib::ustring  FiltradorResultadoHecho::pertenece(const Glib::ustring& )" << std::endl;
    return STR_NULA;
}
