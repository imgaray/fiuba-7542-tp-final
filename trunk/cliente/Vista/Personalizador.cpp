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
#include "VentanaClienteDinamica.h"

Personalizador::Personalizador() {
    Organizacion::cargarDefiniciones();
}

Personalizador::~Personalizador() {
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

void Personalizador::construir() {
    // Tab 1 - test filtrador tab
    Tab* pTab1 = new Tab("Tab 1 - FiltradorTab 1");

    FiltradoresTab* fTab1 = new FiltradoresTab();
    fTab1->agregarEntrada("Vendedor");


    hijos.push_back(fTab1);
    pTab1->pack_start(*fTab1, false, false);
    while (fTab1->tieneFiltrosConsultantes())
        pTab1->agregarConsultante(fTab1->getFiltroConsultante());
    while (fTab1->tieneFiltrosNavegables())
        pTab1->agregarFiltroNavegable(fTab1->getFiltroNavegable());

    pTab1->informarFinCreacion();

    tabs.push_back(pTab1);


    // Tab 2 - test dos inputs
    Tab* pTab2 = new Tab("Tab 2 - input");
    FiltradoresTab* fTab2 = new FiltradoresTab();
    fTab2->agregarEntrada("Sucursal");
    while (fTab2->tieneFiltrosConsultantes())
        pTab2->agregarConsultante(fTab2->getFiltroConsultante());
    while (fTab2->tieneFiltrosNavegables())
        pTab2->agregarFiltroNavegable(fTab2->getFiltroNavegable());

    hijos.push_back(fTab2);

    pTab2->pack_start(*fTab2, false, false);

    pTab2->informarFinCreacion();

    tabs.push_back(pTab2);

    // Tab 3 - test gráfico de torta simple
    Tab* pTab3 = new Tab("Tab 3 - Torta simple");
    FiltradoresTab* fTab3 = new FiltradoresTab();
    while (fTab3->tieneFiltrosConsultantes())
        pTab3->agregarConsultante(fTab3->getFiltroConsultante());
    while (fTab3->tieneFiltrosNavegables())
        pTab3->agregarFiltroNavegable(fTab3->getFiltroNavegable());

    Panel* pPanelTorta3 = new Panel();
    FiltradoresPanel* fPanel3 = new FiltradoresPanel(*fTab3);
    fPanel3->agregarFiltro("Sucursal", "San Julian");
    fPanel3->agregarResultado("Producto");
    fPanel3->agregarResultado(Organizacion::nombreHecho(0), "CONT");
    while (fPanel3->tieneFiltrosConsultantes())
        pTab3->agregarConsultante(fPanel3->getFiltroConsultante());
    while (fPanel3->tieneFiltrosNavegables())
        pTab3->agregarFiltroNavegable(fPanel3->getFiltroNavegable());

    Grafico* pGraficoTorta3 = new GraficoDeTorta(*fPanel3);
    pTab3->agregarConsultante(pGraficoTorta3);
    pPanelTorta3->setContenido(*pGraficoTorta3);

    Gtk::HSeparator* sep3 = new Gtk::HSeparator();
    Gtk::Table* pTable3 = new Gtk::Table(1, 1, true);
    pTable3->attach(*pPanelTorta3, 0, 1, 0, 1);

    hijos.push_back(fTab3);
    hijos.push_back(fPanel3);
    hijos.push_back(pGraficoTorta3);
    hijos.push_back(pPanelTorta3);
    hijos.push_back(sep3);
    hijos.push_back(pTable3);

    pTab3->pack_start(*fTab3, false, false);
    pTab3->pack_start(*sep3, false, false);
    pTab3->pack_start(*pTable3, true, true);

    pTab3->informarFinCreacion();

    tabs.push_back(pTab3);

//    // Tab 3 - Barras simple
//    Tab* pTab3 = new Tab("Tab 2 - Barras simple");
//    FiltradoresTab* fTab3 = new FiltradoresTab();
//    fTab3->agregarEntrada("Producto");
//    while (fTab3->tieneFiltrosConsultantes())
//        pTab3->agregarConsultante(fTab3->getFiltroConsultante());
//    while (fTab3->tieneFiltrosNavegables())
//        pTab3->agregarFiltroNavegable(fTab3->getFiltroNavegable());
//
//    Panel* pPanelBarras3 = new Panel();
//    FiltradoresPanel* fPanel3 = new FiltradoresPanel(*fTab2);
//    fPanel3->agregarResultado("Marca");
//    fPanel3->agregarResultado(Organizacion::nombreHecho(1), "CONT");
//    while (fPanel3->tieneFiltrosConsultantes())
//        pTab3->agregarConsultante(fPanel3->getFiltroConsultante());
//    while (fPanel3->tieneFiltrosNavegables())
//        pTab3->agregarFiltroNavegable(fPanel3->getFiltroNavegable());
//
//    Grafico* pGraficoBarras3 = new GraficoDeBarras(*fPanel3);
//    pTab3->agregarConsultante(pGraficoBarras3);
//    pPanelBarras3->setContenido(*pGraficoBarras3);
//
//    Gtk::HSeparator* sep3 = new Gtk::HSeparator();
//    Gtk::Table* pTable3 = new Gtk::Table(1, 1, true);
//    pTable3->attach(*pPanelBarras3, 0, 1, 0, 1);
//
//    hijos.push_back(fTab3);
//    hijos.push_back(fPanel3);
//    hijos.push_back(pGraficoBarras3);
//    hijos.push_back(pPanelBarras3);
//    hijos.push_back(sep3);
//    hijos.push_back(pTable3);
//
//    pTab3->pack_start(*fTab3, false, false);
//    pTab3->pack_start(*sep3, false, false);
//    pTab3->pack_start(*pTable3, true, true);
//
//    tabs.push_back(pTab3);

//    fPanel1->agregarEntrada("Marca");
//    FiltradoresPanel* fPanel1_1 = new FiltradoresPanel(*fTab1);
//    FiltradoresPanel* fPanel1_2 = new FiltradoresPanel(*fTab1);
//
////    fPanel1_1->agregarEntrada("Marca");
//    fPanel1_1->agregarResultado("Producto");
//
//    fPanel1_2->agregarFiltro("Sucursal", "Avellaneda");
//    fPanel1_2->agregarResultado("Marca");
//    fPanel1_2->agregarResultado("PrecioLista", "SUM");
//
//    Grafico* gBarras1 = new GraficoDeBarras(*fPanel1_1);
//    Grafico* gTorta1 = new GraficoDeTorta(*fPanel1_2);
//
//    Panel* pPanBarras1 = new Panel(*gBarras1, gBarras1->getFiltrador());
//    Panel* pPanTorta1 = new Panel(*gTorta1, gTorta1->getFiltrador());
//
//    Gtk::HSeparator* sep1 = new Gtk::HSeparator();
//    Gtk::Table* pTable1 = new Gtk::Table(2, 2, true);
//    pTable1->attach(*pPanTorta1, 0, 1, 0, 1);
//    pTable1->attach(*pPanBarras1, 0, 1, 1, 2);
//
//    hijos.push_back(gBarras1);
//    hijos.push_back(gTorta1);
//    hijos.push_back(fTab1);
//    hijos.push_back(fPanel1_1);
//    hijos.push_back(fPanel1_2);
//    hijos.push_back(pPanBarras1);
//    hijos.push_back(pPanTorta1);
//    hijos.push_back(sep1);
//    hijos.push_back(pTable1);
//
//    pTab1->pack_start(*fTab1, false, false);
//    pTab1->pack_start(*sep1, false, false);
//    pTab1->pack_start(*pTable1, true, true);
//
//    pTab2->agregarConsultante(fTab1);
//    pTab2->agregarConsultante(pPanBarras1);
//    pTab2->agregarConsultante(pPanTorta1);
//
//    tabs.push_back(pTab2);
//
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

    if (archivo.is_open())
        archivo.close();
}
