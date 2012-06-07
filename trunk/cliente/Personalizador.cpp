#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"

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

Gtk::Table& Personalizador::siguiente() {
    return **it++;
}

void Personalizador::construir() {
    Gtk::Table* pTable1 = new Gtk::Table(2, 2, true);
    Gtk::Table* pTable2 = new Gtk::Table(3, 3, true);
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

    pTable1->attach(*gTorta1, 0, 1, 0, 1);
    pTable1->attach(*gBarras1, 0, 1, 1, 2);
    tabs.push_back(pTable1);

    pTable2->attach(*gTorta2, 0, 2, 0, 1);
    pTable2->attach(*gBarras2, 1, 2, 1, 2);
    pTable2->attach(*gTorta3, 0, 2, 2, 3);
    pTable2->attach(*gBarras3, 2, 3, 0, 3);
    tabs.push_back(pTable2);

    it = tabs.begin();
}
