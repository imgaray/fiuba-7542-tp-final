#include <gtkmm/separator.h>
#include <gtkmm/table.h>
#include <gtkmm/adjustment.h>
#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Tab.h"
#include "Panel.h"
#include "FiltradoresTab.h"
#include "FiltradoresPanel.h"
#include "Organizacion.h"

Personalizador::Personalizador() {
    Organizacion::cargarDefiniciones();
}

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

///** @todo este método DEBE irse */
//#include <iostream>
//Filtrador* getFiltradorPanel(int i, Filtrador* f) {
//    Filtros filtros;
//    Entradas entradasTab;
//    Entradas entradasPanel;
//    switch (i%2) {
//        case 0: filtros["Sucursal"] = "San Telmo";
//                filtros["Marca"] = "Apple";
//                break;
//        case 1: filtros["Sucursal"] = "Puerto Madero";
//                break;
//        default:
//            std::cout << "You are not supposed to be here, you know?" << std::endl;
//            break;
//    }
//    entradasTab["Vendedor"] = "María";
//    switch (i%2) {
//        case 0: entradasPanel["Marca"] = "Apple";
//                break;
//        case 1: entradasPanel["Vendedor"] = "Gonzalo";
//                entradasPanel["Producto"] = "iPhone";
//                break;
//        default:
//            std::cout << "You are not supposed to be here, you know?" << std::endl;
//            break;
//    }
//    if (f)
//        return new Filtrador(*f, entradasPanel);
//    else
//        return new Filtrador(filtros, entradasTab);
//}
void Personalizador::construir() {
    // Tab 1
    Tab* pTab1 = new Tab(0, "Tab 1 - Torta+Barra");
    std::cout << "Pt: " << pTab1 << std::endl;

    FiltradoresTab* fTab1 = new FiltradoresTab();
    std::cout << "Pft: " << fTab1 << std::endl;
    fTab1->agregarEntrada("Vendedor");

    FiltradoresPanel* fPanel1_1 = new FiltradoresPanel(*fTab1);
    std::cout << "Pfp: " << fPanel1_1 << std::endl;
//    FiltradoresPanel* fPanel1_2 = new FiltradoresPanel(*fTab1);

    fPanel1_1->agregarEntrada("Marca");

    Grafico* gBarras1 = new GraficoDeBarras(*fPanel1_1);
    std::cout << "Cg: " << gBarras1 << std::endl;
//    Grafico* gTorta1 = new GraficoDeTorta(*fPanel1_2);

    Panel* pPanBarras1 = new Panel(*gBarras1, gBarras1->getFiltrador());
    std::cout << "Pp: " << pPanBarras1 << std::endl;
//    Panel* pPanTorta1 = new Panel(*gTorta1, gTorta1->getFiltrador());

    Gtk::HSeparator* sep1 = new Gtk::HSeparator();
    Gtk::Table* pTable1 = new Gtk::Table(2, 2, true);
//    pTable1->attach(*pPanTorta1, 0, 1, 0, 1);
    pTable1->attach(*pPanBarras1, 0, 1, 1, 2);

    hijos.push_back(gBarras1);
//    hijos.push_back(gTorta1);
    hijos.push_back(fTab1);
    hijos.push_back(fPanel1_1);
//    hijos.push_back(fPanel1_2);
    hijos.push_back(pPanBarras1);
//    hijos.push_back(pPanTorta1);
    hijos.push_back(sep1);
    hijos.push_back(pTable1);

    pTab1->pack_start(*fTab1, false, false);
    pTab1->pack_start(*sep1, false, false);
    pTab1->pack_start(*pTable1, true, true);

    pTab1->agregarConsultante(fTab1);
    pTab1->agregarConsultante(pPanBarras1);
//    pTab1->agregarConsultante(pPanTorta1);

    tabs.push_back(pTab1);

//    // Tab 2
//    Tab* pTab2 = new Tab(0, "Tab 2 - Mezcla dipersada");
//    FiltradoresTab* fTab2 = new FiltradoresTab();
//    fTab2->agregarEntrada("Sucursal");
//    fTab2->agregarEntrada("Vendedor");
//
//    FiltradoresPanel* fPanel2_1 = new FiltradoresPanel(*fTab2);
//    FiltradoresPanel* fPanel2_2 = new FiltradoresPanel(*fTab2);
//    FiltradoresPanel* fPanel2_3 = new FiltradoresPanel(*fTab2);
//    FiltradoresPanel* fPanel2_4 = new FiltradoresPanel(*fTab2);
//
//    Grafico* gBarras2 = new GraficoDeBarras(*fPanel2_1);
//    Grafico* gTorta2 = new GraficoDeTorta(*fPanel2_2);
//    Grafico* gBarras3 = new GraficoDeBarras(*fPanel2_3);
//    Grafico* gTorta3 = new GraficoDeTorta(*fPanel2_4);
//
//    Panel* pPanBarras2 = new Panel(*gBarras2, gBarras2->getFiltrador());
//    Panel* pPanTorta2 = new Panel(*gTorta2, gTorta2->getFiltrador());
//    Panel* pPanBarras3 = new Panel(*gBarras3, gBarras3->getFiltrador());
//    Panel* pPanTorta3 = new Panel(*gTorta3, gTorta3->getFiltrador());
//
//    Gtk::HSeparator* sep2 = new Gtk::HSeparator();
//    Gtk::Table* pTable2 = new Gtk::Table(3, 3, true);
//    pTable2->attach(*pPanTorta2, 0, 2, 0, 1);
//    pTable2->attach(*pPanBarras2, 1, 2, 1, 2);
//    pTable2->attach(*pPanTorta3, 0, 2, 2, 3);
//    pTable2->attach(*pPanBarras3, 2, 3, 0, 3);
//
//    hijos.push_back(gBarras2);
//    hijos.push_back(gTorta2);
//    hijos.push_back(gBarras3);
//    hijos.push_back(gTorta3);
//    hijos.push_back(fTab2);
//    hijos.push_back(fPanel2_1);
//    hijos.push_back(fPanel2_2);
//    hijos.push_back(fPanel2_3);
//    hijos.push_back(fPanel2_4);
//    hijos.push_back(pPanBarras2);
//    hijos.push_back(pPanTorta2);
//    hijos.push_back(pPanBarras3);
//    hijos.push_back(pPanTorta3);
//    hijos.push_back(sep2);
//    hijos.push_back(pTable2);
//
//    pTab2->pack_start(*fTab2, false, false);
//    pTab2->pack_start(*sep2, false, false);
//    pTab2->pack_start(*pTable2, true, true);
//
//    pTab2->agregarConsultante(fTab2);
//    pTab2->agregarConsultante(pPanBarras2);
//    pTab2->agregarConsultante(pPanTorta2);
//    pTab2->agregarConsultante(pPanBarras3);
//    pTab2->agregarConsultante(pPanTorta3);
//
//    tabs.push_back(pTab2);

    it = tabs.begin();
}
