#include "Filtradores.h"
#include "Filtrador.h"

Filtradores::Filtradores()
: cant_inputs(0), inputsDisponibles(0),
  _puedeFiltrar(true) {}

Filtradores::~Filtradores() {}

bool Filtradores::puedeFiltrar() {
    return _puedeFiltrar;
}

void Filtradores::filtrar(Consulta& c) {
    std::list< Filtrador* >::iterator it = filtradores.begin();
    for ( ; it != filtradores.end(); ++it)
        (*it)->filtrar(c);
}

bool Filtradores::tieneFiltrosNavegables() {
    return !filtrosNavegables.empty();
}

bool Filtradores::tieneFiltrosConsultantes() {
    return !filtrosConsultantes.empty();
}

FiltradorInput* Filtradores::getFiltroNavegable() {
    FiltradorInput* f = filtrosNavegables.front();
    filtrosNavegables.pop();
    return f;
}

FiltradorInputDimension* Filtradores::getFiltroConsultante() {
    FiltradorInputDimension* f = filtrosConsultantes.front();
    filtrosConsultantes.pop();
    return f;
}

void Filtradores::on_input_esta_disponible(bool estado) {
    if (estado)
        ++inputsDisponibles;
    else
        --inputsDisponibles;

    _puedeFiltrar = inputsDisponibles == cant_inputs;
}
