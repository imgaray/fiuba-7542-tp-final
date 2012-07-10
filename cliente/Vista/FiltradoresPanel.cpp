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
#include "FiltradorPivoteX.h"
#include "FiltradorPivoteY.h"

#define EXCEP_MSJ_FILTRO_MAL    "El campo solicitado para el filtro no es dimensión ni hecho"
#define EXCEP_MSJ_INPUT_MAL     "El campo solicitado para el input no es dimensión ni hecho"
#define EXCEP_MSJ_TABLA_P_MAL     "El campo solicitado para la tabla pivote no es dimensión ni hecho"
#define EXCEP_MSJ_TABLA_P_RESULTADO_MAL     "La tabla pivote sólo admite hechos en sus resultados"

FiltradoresPanel::FiltradoresPanel(FiltradoresTab& filtTab)
: filtrosHeredados(filtTab),
  esParaTablaPivote(false) {}

FiltradoresPanel::~FiltradoresPanel() {}

bool FiltradoresPanel::puedeFiltrar() {
    return _puedeFiltrar && filtrosHeredados.puedeFiltrar();
}

void FiltradoresPanel::agregarFiltro(const std::string& filtro,
                                     const std::string& valor) {
    FiltradorFiltroDimension* f = manage(new FiltradorFiltroDimension(filtro, valor));
    add(*f);
    filtradores.push_back(f);
}

void FiltradoresPanel::agregarFiltro(const std::string& filtro,
                                     const std::string& valorCombo,
                                     const std::string& valorEntrada) {
    FiltradorFiltro* f;
    try {
        if (Organizacion::esDimensionEspecial(filtro))
            f = manage(new FiltradorFiltroFecha(filtro, valorCombo, valorEntrada));
        else
            f = manage(new FiltradorFiltroHecho(filtro, valorCombo, valorEntrada));

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
                f = manage(new FiltradorInputFecha(entrada));
            else {
                f = manage(new FiltradorInputDimension(entrada));
                filtrosConsultantes.push((FiltradorInputDimension* ) f);
            }
        } else {
            if (Organizacion::esHecho(entrada))
                f = manage(new FiltradorInputHecho(entrada));
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_INPUT_MAL);
        }
        add(*f);
        filtradores.push_back(f);
        filtrosNavegables.push(f);
        ++cant_inputs;

        f->signal_navegabilidad().connect(sigc::mem_fun(*this,
            &FiltradoresPanel::on_signal_navegabilidad));

        f->signal_input_disponible().connect(sigc::mem_fun(*this,
            &FiltradoresPanel::on_input_esta_disponible));
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarResultado(const std::string& dimension) {
    try {
        if (esParaTablaPivote)
            throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_TABLA_P_RESULTADO_MAL);

        FiltradorResultadoDimension* f = manage(
            new FiltradorResultadoDimension(dimension));
        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarResultado(const std::string& fecha,
                                        const std::string& valorCombo,
                                        const std::string& valorEntrada) {
    FiltradorResultadoFecha* f;
    try {
        if (esParaTablaPivote)
            throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_TABLA_P_RESULTADO_MAL);

        f = manage(new FiltradorResultadoFecha(fecha, valorCombo, valorEntrada));
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
        f = manage(new FiltradorResultadoHecho(hecho, agregacion));
        add(*f);
        filtradores.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarXTablaP(const std::string& valor) {
    FiltradorPivoteX* f;
    try {
        if (!Organizacion::esDimension(valor) &&
            !Organizacion::esHecho(valor))
            throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_TABLA_P_MAL);

        f = manage(new FiltradorPivoteX(valor));
        add(*f);
        filtradores.push_back(f);
        esParaTablaPivote = true;
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::agregarYTablaP(const std::string& valor) {
    FiltradorPivoteY* f;
    try {
        if (!Organizacion::esDimension(valor) &&
            !Organizacion::esHecho(valor))
            throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_TABLA_P_MAL);

        f = manage(new FiltradorPivoteY(valor));
        add(*f);
        filtradores.push_back(f);
        esParaTablaPivote = true;
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}

void FiltradoresPanel::filtrar(Consulta& c) {
    if (esParaTablaPivote)
        c.definirConsultaDeTablaPivote();

    filtrosHeredados.filtrar(c);
    Filtradores::filtrar(c);
}

sigc::signal< void > FiltradoresPanel::signal_navegabilidad() {
    return signal_navegabilidad_seleccionada;
}

void FiltradoresPanel::on_signal_navegabilidad() {
    signal_navegabilidad_seleccionada.emit();
}
