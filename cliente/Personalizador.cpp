#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"

Personalizador::Personalizador() {}

Personalizador::~Personalizador() {
    if (archivo.is_open())
        archivo.close();
    /** @todo recorrer listas y deleeeete todo. Quizás haya que sacarle el padre a los widgets */
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
//    Gtk::Table* pTable2 = new Gtk::Table(3, 3, true);
    Grafico* gBarras = new GraficoDeBarras();
    Grafico* gTorta = new GraficoDeTorta();
    hijos.push_back(gBarras);
    hijos.push_back(gTorta);

    pTable1->attach(*gTorta, 0, 1, 0, 1);
    pTable1->attach(*gBarras, 0, 1, 1, 2);
    tabs.push_back(pTable1);

    it = tabs.begin();
}
