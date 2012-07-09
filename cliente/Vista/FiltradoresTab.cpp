#include "FiltradoresTab.h"
#include "Organizacion.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Filtrador.h"
#include "FiltradorInputDimension.h"
#include "FiltradorInputFecha.h"
#include "FiltradorInputHecho.h"

#define EXCEP_MSJ_INPUT_MAL     "El campo solicitado para el input no es dimensión ni hecho"

FiltradoresTab::FiltradoresTab() {}

FiltradoresTab::~FiltradoresTab() {}

void FiltradoresTab::agregarEntrada(const std::string& entrada) {
    FiltradorInput* f;
    try {
        if (Organizacion::esDimension(entrada)) {
            if (Organizacion::esDimensionEspecial(entrada))
                f = manage(new FiltradorInputFecha(entrada));
            else{
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

        f->signal_input_disponible().connect(sigc::mem_fun(*this,
            &FiltradoresTab::on_input_esta_disponible));
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}
