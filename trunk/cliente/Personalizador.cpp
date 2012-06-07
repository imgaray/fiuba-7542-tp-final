#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Tab.h"


Personalizador::Personalizador() {}

Personalizador::~Personalizador() {
    if (archivo.is_open())
        archivo.close();
    /** @todo recorrer listas y deleeeete todo. Quizás haya que sacarle el padre a los widgets */
    it = tabs.begin();
    for ( ; it != tabs.end(); ++it)
        delete *it;

    std::list< Gtk::Widget* >::iterator itHijos = hijos.begin();
    for ( ; itHijos != hijos.end(); ++itHijos)
        delete *itHijos;
}

/** @todo hacerlo con archivo!!! */
bool Personalizador::personalizarDesdeArchivo(const char* nombreArch) {
//    ifstream.open(nombreArch);
//    if (ifstrea.is_open()) {
    if (true) { // mientras no haya archivo
        construir();
        return true;
    }
    else
        return false;
}

bool Personalizador::tieneSiguiente() {
    return it != tabs.end();
}

Tab& Personalizador::siguiente() {
    return **it++;
}

void Personalizador::construir() {
    Tab* pTab1 = new Tab(2, 2, true, "Tab 1 - Torta+Barra");
    Tab* pTab2 = new Tab(3, 3, true, "Tab 2 - Mezcla dipersada");
    Grafico* gBarras1 = new GraficoDeBarras();
    Grafico* gTorta1 = new GraficoDeTorta();
    Grafico* gBarras2 = new GraficoDeBarras();
    Grafico* gTorta2 = new GraficoDeTorta();
    Grafico* gBarras3 = new GraficoDeBarras();
    Grafico* gTorta3 = new GraficoDeTorta();
    hijos.push_back(gBarras1);
    hijos.push_back(gTorta1);
    hijos.push_back(gBarras2);
    hijos.push_back(gTorta2);
    hijos.push_back(gBarras3);
    hijos.push_back(gTorta3);

    pTab1->attach(*gTorta1, 0, 1, 0, 1);
    pTab1->attach(*gBarras1, 0, 1, 1, 2);
    tabs.push_back(pTab1);

    pTab2->attach(*gTorta2, 0, 2, 0, 1);
    pTab2->attach(*gBarras2, 1, 2, 1, 2);
    pTab2->attach(*gTorta3, 0, 2, 2, 3);
    pTab2->attach(*gBarras3, 2, 3, 0, 3);
    tabs.push_back(pTab2);

    it = tabs.begin();
}
