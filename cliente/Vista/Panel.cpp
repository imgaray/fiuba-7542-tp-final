#include "Panel.h"
#include "Grafico.h"
#include "Filtrador.h"

Panel::Panel(Grafico& g, Filtrador& f) : grafico(g), filtrador(f) {
    pack_start(filtrador, false, false);
    add(grafico);
}

Panel::~Panel() {}

