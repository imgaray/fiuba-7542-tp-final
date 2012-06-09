#include <gtkmm/separator.h>
#include <gtkmm/table.h>
#include <gtkmm/adjustment.h>
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
    /** @todo quizás haya que sacarle el padre a los widgets */
    it = tabs.begin();
    for ( ; it != tabs.end(); ++it)
        delete *it;

    std::list< Gtk::Object* >::iterator itHijos = hijos.begin();
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
Filtrador* getFiltradorPanel(int i, Filtrador* f) {
    Filtros filtros;
    Entradas entradasTab;
    Entradas entradasPanel;
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
    entradasTab["Vendedor"] = "María";
    switch (i%2) {
        case 0: entradasPanel["Marca"] = "Apple";
                break;
        case 1: entradasPanel["Vendedor"] = "Gonzalo";
                entradasPanel["Producto"] = "iPhone";
                break;
        default:
            std::cout << "You are not supposed to be here, you know?" << std::endl;
            break;
    }
    if (f)
        return new Filtrador(*f, entradasPanel);
    else
        return new Filtrador(filtros, entradasTab);
}
void Personalizador::construir() {
    Tab* pTab1 = new Tab(0, "Tab 1 - Torta+Barra");
    Tab* pTab2 = new Tab(0, "Tab 2 - Mezcla dipersada");
    Filtrador* f7 = getFiltradorPanel(0, 0);
    Filtrador* f8 = getFiltradorPanel(1, 0);
    Filtrador* f1 = getFiltradorPanel(0, f7);
    Filtrador* f2 = getFiltradorPanel(0, f7);
    Filtrador* f3 = getFiltradorPanel(1, f8);
    Filtrador* f4 = getFiltradorPanel(1, f8);
    Filtrador* f5 = getFiltradorPanel(1, f8);
    Filtrador* f6 = getFiltradorPanel(1, f8);
    Grafico* gBarras1 = new GraficoDeBarras(*f1);
    Grafico* gTorta1 = new GraficoDeTorta(*f2);
    Grafico* gBarras2 = new GraficoDeBarras(*f3);
    Grafico* gTorta2 = new GraficoDeTorta(*f4);
    Grafico* gBarras3 = new GraficoDeBarras(*f5);
    Grafico* gTorta3 = new GraficoDeTorta(*f6);
    Panel* pPanBarras1 = new Panel(*gBarras1, *f1);
    Panel* pPanTorta1 = new Panel(*gTorta1, *f2);
    Panel* pPanBarras2 = new Panel(*gBarras2, *f3);
    Panel* pPanTorta2 = new Panel(*gTorta2, *f4);
    Panel* pPanBarras3 = new Panel(*gBarras3, *f5);
    Panel* pPanTorta3 = new Panel(*gTorta3, *f6);
    Gtk::HSeparator* sep1 = new Gtk::HSeparator();
    Gtk::HSeparator* sep2 = new Gtk::HSeparator();
    Gtk::Table* pTable1 = new Gtk::Table(2, 2, true);
    Gtk::Table* pTable2 = new Gtk::Table(3, 3, true);
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
    hijos.push_back(f7);
    hijos.push_back(f8);
    hijos.push_back(pPanBarras1);
    hijos.push_back(pPanTorta1);
    hijos.push_back(pPanBarras2);
    hijos.push_back(pPanTorta2);
    hijos.push_back(pPanBarras3);
    hijos.push_back(pPanTorta3);
    hijos.push_back(sep1);
    hijos.push_back(sep2);
    hijos.push_back(pTable1);
    hijos.push_back(pTable2);

    pTable1->attach(*pPanTorta1, 0, 1, 0, 1);
    pTable1->attach(*pPanBarras1, 0, 1, 1, 2);

    pTable2->attach(*pPanTorta2, 0, 2, 0, 1);
    pTable2->attach(*pPanBarras2, 1, 2, 1, 2);
    pTable2->attach(*pPanTorta3, 0, 2, 2, 3);
    pTable2->attach(*pPanBarras3, 2, 3, 0, 3);

    pTab1->pack_start(*f7, false, false);
    pTab1->pack_start(*sep1, false, false);
    pTab1->pack_start(*pTable1, true, true);

    pTab2->pack_start(*f8, false, false);
    pTab2->pack_start(*sep2, false, false);
    pTab2->pack_start(*pTable2, true, true);

    tabs.push_back(pTab1);
    tabs.push_back(pTab2);

    it = tabs.begin();
}
