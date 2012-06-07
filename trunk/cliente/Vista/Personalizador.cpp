#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Tab.h"
#include "Panel.h"
#include "Filtrador.h"


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

/** @todo este método DEBE irse */
#include <iostream>
Filtrador* getFiltrador() {
    static int i = 0;
    Filtros filtros;
    Entradas entradas;
    switch (i%2) {
        case 0: filtros["Sucursal"] = "San Telmo";
                filtros["Marca"] = "Apple";
                break;
        case 1: filtros["Sucursal"] = "Puerto Madero";
                break;
        default:
            std::cout << "You are not supposed to be here, you know?" << std::endl;
            break;
    }
    switch (i%3) {
        case 0: entradas["Vendedor"] = "María";
                break;
        case 1: entradas["Marca"] = "Apple";
                break;
        case 2: entradas["Vendedor"] = "Gonzalo";
                entradas["Producto"] = "iPhone";
                break;
        default:
            std::cout << "You are not supposed to be here, you know?" << std::endl;
            break;
    }

    ++i;
    return new Filtrador(filtros, entradas);
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
    Filtrador* f1 = getFiltrador();
    Filtrador* f2 = getFiltrador();
    Filtrador* f3 = getFiltrador();
    Filtrador* f4 = getFiltrador();
    Filtrador* f5 = getFiltrador();
    Filtrador* f6 = getFiltrador();
    Panel* pPanBarras1 = new Panel(*gBarras1, *f1);
    Panel* pPanTorta1 = new Panel(*gTorta1, *f2);
    Panel* pPanBarras2 = new Panel(*gBarras2, *f3);
    Panel* pPanTorta2 = new Panel(*gTorta2, *f4);
    Panel* pPanBarras3 = new Panel(*gBarras3, *f5);
    Panel* pPanTorta3 = new Panel(*gTorta3, *f6);
    hijos.push_back(gBarras1);
    hijos.push_back(gTorta1);
    hijos.push_back(gBarras2);
    hijos.push_back(gTorta2);
    hijos.push_back(gBarras3);
    hijos.push_back(gTorta3);
    hijos.push_back(f1);
    hijos.push_back(f2);
    hijos.push_back(f3);
    hijos.push_back(f4);
    hijos.push_back(f5);
    hijos.push_back(f6);
    hijos.push_back(pPanBarras1);
    hijos.push_back(pPanTorta1);
    hijos.push_back(pPanBarras2);
    hijos.push_back(pPanTorta2);
    hijos.push_back(pPanBarras3);
    hijos.push_back(pPanTorta3);

    pTab1->attach(*pPanTorta1, 0, 1, 0, 1);
    pTab1->attach(*pPanBarras1, 0, 1, 1, 2);
    tabs.push_back(pTab1);

    pTab2->attach(*pPanTorta2, 0, 2, 0, 1);
    pTab2->attach(*pPanBarras2, 1, 2, 1, 2);
    pTab2->attach(*pPanTorta3, 0, 2, 2, 3);
    pTab2->attach(*pPanBarras3, 2, 3, 0, 3);
    tabs.push_back(pTab2);

    it = tabs.begin();
}