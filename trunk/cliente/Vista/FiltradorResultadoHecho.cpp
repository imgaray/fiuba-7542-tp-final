#include "FiltradorResultadoHecho.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Consulta.h"
#include "FiltradorHelper.h"

FiltradorResultadoHecho::FiltradorResultadoHecho(const Glib::ustring& _hecho,
    const Glib::ustring& _agregacion)
    : FiltradorResultado(STR_NULA), hecho(_hecho) {
    const FiltradorHelper& helper = FiltradorHelper::getInstancia();

    i = helper.perteneceAlAgregacionesPosibles(_agregacion);
    if (i == NO_PERTENECE) {
        std::string msj = "No pertenece al conjunto de agregaciones posibles: ";
        msj += _agregacion.c_str();
        throw ExcepcionFiltradorMalConstruido(msj.c_str());
    }


    Glib::ustring label = _agregacion;
    label += "(";
    label += hecho;
    label += ")";
    setResultado(label);

    agregacion = helper.getAgregacion(i);
}

FiltradorResultadoHecho::~FiltradorResultadoHecho() {}

void FiltradorResultadoHecho::filtrar(Consulta& c) {
    c.defininirAgregacion(agregacion, hecho);
}

