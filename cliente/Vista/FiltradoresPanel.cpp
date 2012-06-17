#include "FiltradoresPanel.h"
#include "FiltradoresTab.h"
#include "Organizacion.h"
#include <iostream>
#include "ExcepcionFiltradorMalConstruido.h"
#include "ExcepcionFiltradorExistente.h"
#include "Filtrador.h"
#include "FiltradorFiltroDimension.h"
#include "FiltradorFiltroFecha.h"
#include "FiltradorFiltroHecho.h"
#include "FiltradorInputDimension.h"
#include "FiltradorInputFecha.h"
#include "FiltradorInputHecho.h"
#include "FiltradorResultadoDimension.h"
#include "FiltradorResultadoFecha.h"
#include "FiltradorResultadoHecho.h"

#define EXCEP_MSJ_FILTRO_MAL    "El campo solicitado para el filtro no es dimensión ni hecho"
#define EXCEP_MSJ_INPUT_MAL     "El campo solicitado para el input no es dimensión ni hecho"

FiltradoresPanel::FiltradoresPanel() {}

FiltradoresPanel::~FiltradoresPanel() {
    std::list< Filtrador* >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        delete *it;
}

/** @todo verificar que el filtro/input/resultado no exista ya */
void FiltradoresPanel::agregarFiltro(const std::string& filtro,
                                     const std::string& valor) {
    FiltradorFiltroDimension* f = new FiltradorFiltroDimension(filtro, valor);
    add(*f);
    filtradores.push_back(f);
}

void FiltradoresPanel::agregarFiltro(const std::string& filtro,
                                     const std::string& valorCombo,
                                     const std::string& valorEntrada) {
    FiltradorFiltro* f;
    try {
        if (Organizacion::esDimensionEspecial(filtro))
            f = new FiltradorFiltroFecha(filtro, valorCombo, valorEntrada);
        else
            f = new FiltradorFiltroHecho(filtro, valorCombo, valorEntrada);

        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarEntrada(const std::string& entrada) {
    FiltradorInput* f;
    try {
        if (Organizacion::esDimension(entrada)) {
            if (Organizacion::esDimensionEspecial(entrada))
                f = new FiltradorInputFecha(entrada);
            else
                f = new FiltradorInputDimension(entrada);
        } else {
            if (Organizacion::esHecho(entrada))
                f = new FiltradorInputHecho(entrada);
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_INPUT_MAL);
        }
        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarResultado(const std::string& dimension) {
    FiltradorResultadoDimension* f = new FiltradorResultadoDimension(dimension);
    add(*f);
    filtradores.push_back(f);
}

void FiltradoresPanel::agregarResultado(const std::string& fecha,
                                        const std::string& valorCombo,
                                        const std::string& valorEntrada) {
    FiltradorResultadoFecha* f;
    try {
        f = new FiltradorResultadoFecha(fecha, valorCombo, valorEntrada);
        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarResultado(const std::string& hecho,
                                        const std::string& agregacion) {
    FiltradorResultadoHecho* f;
    try {
        f = new FiltradorResultadoHecho(hecho, agregacion);
        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}
