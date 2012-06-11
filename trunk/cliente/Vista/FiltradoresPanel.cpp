#include "FiltradoresPanel.h"
#include "Organizacion.h"
#include <iostream>
#include "ExcepcionFiltradorMalConstruido.h"
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

FiltradoresPanel::FiltradoresPanel(FiltradoresTab& filtTab)
: filtrosHeredados(filtTab) {}

FiltradoresPanel::~FiltradoresPanel() {}

void FiltradoresPanel::agregarFiltro(const std::string& filtro,
                                     const std::string& valor) {
    Filtrador* f;
    try {
        if (Organizacion::esDimension(filtro)) {
            if (Organizacion::esDimensionEspecial(filtro))
                f = new FiltradorFiltroFecha(filtro, valor);
            else
                f = new FiltradorFiltroDimension(filtro, valor);
        } else {
            if (Organizacion::esHecho(filtro))
                f = new FiltradorFiltroHecho(filtro, valor);
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_FILTRO_MAL);
        }
        add(*f);
        widgets.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarEntrada(const std::string& entrada) {
    Filtrador* f;
    try {
        if (Organizacion::esDimension(entrada)) {
            if (Organizacion::esDimensionEspecial(entrada))
                f = new FiltradorInputFecha(entrada);
            else {
                f = new FiltradorInputDimension(entrada);
                Consultante* c = dynamic_cast< Consultante* >(f);
                if (c)
                    agregarConsultante(c);
            }
        } else {
            if (Organizacion::esHecho(entrada))
                f = new FiltradorInputHecho(entrada);
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_INPUT_MAL);
        }
        add(*f);
        widgets.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarResultado(const std::string& dimension) {
    FiltradorResultadoDimension* f = new FiltradorResultadoDimension(dimension);
    add(*f);
    widgets.push_back(f);
}

void FiltradoresPanel::agregarResultado(const std::string& fecha,
                                        const std::string& valorCombo,
                                        const std::string& valorEntrada) {
    FiltradorResultadoFecha* f;
    try {
        f = new FiltradorResultadoFecha(fecha, valorCombo, valorEntrada);
        add(*f);
        widgets.push_back(f);
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
        widgets.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}


