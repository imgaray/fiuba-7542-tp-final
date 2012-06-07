#include "Panel.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Grafico.h"

Panel::Panel(Grafico& g) : grafico(g) {
    pack_end(g);
}

Panel::~Panel() {}

