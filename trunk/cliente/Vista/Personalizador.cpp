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
#include "TablaComun.h"
//#include <libxml++/libxml++.h>

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
//    nombreArchivo = nombreArch;
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

/*
void construir_filtro(xmlpp::Node& filtro) {
	
}

void construir_panel(xmlpp::Node& panel) {
	
}

void Personalizador::construir_tab(xmlpp::Node& tab) {
	// esta lista tiene <filtros>
	Glib::ustring tfiltros = "filtros";
	xmlpp::Node::NodeList nodoFiltros = tab.get_children(tfiltros);
	// esta lista tiene <paneles>
	Glib::ustring tpaneles = "paneles";
	xmlpp::Node::NodeList nodoPaneles = tab.get_children(tpaneles);
	
	// esta lista tiene todos los filtros hijos de <filtros>
	xmlpp::Node::NodeList filtros = nodoFiltros.get_childrem();
	xmlpp::Node::NodeList::iterator iterFiltros;
	for (iterFiltros = filtros..begin(); iterFiltros != filtros.end(); ++iterFiltros) {
		construir_filtro(*iterFiltros);
	}
	
	xmlpp::Node::NodeList paneles = nodoPaneles.get_children();
	xmlpp::Node::NodeList::iterator iterPaneles;
	for (iterPaneles = paneles.begin(); iterPaneles != paneles.end(); ++iterPaneles) {
		construir_panel(*iterPaneles);
	}
}
 
void Personalizador::construir_desde_nodo(const xmlpp::Node* nodo) {
	// esta lista tiene todos los hijos <tab>
	xmlpp::Node::NodeList tabs = node->get_children();
	xmlpp::Node::NodeList::iterator iter;
	for (iter = tabs.begin(); iter != tabs.end(); ++iter) {
		construir_tab(*iter);
	}
}
	const xmlpp::ContentNode* nodeContent = dynamic_cast<const xmlpp::ContentNode*>(node);
	const xmlpp::TextNode* nodeText = dynamic_cast<const xmlpp::TextNode*>(node);
	const xmlpp::CommentNode* nodeComment = dynamic_cast<const xmlpp::CommentNode*>(node);
	
	if(nodeText && nodeText->is_white_space())
		return;
	
	Glib::ustring nodename = node->get_name();
	
	if(!nodeText && !nodeComment && !nodename.empty()) {
		print_indentation(indentation);
		std::cout << "Node name = " << node->get_name() << std::endl;
		std::cout << "Node name = " << nodename << std::endl;
	}
	else if(nodeText) {
		print_indentation(indentation);
		std::cout << "Text Node" << std::endl;
	}
	
	//Treat the various node types differently: 
	if(nodeText) {
		print_indentation(indentation);
		std::cout << "text = \"" << nodeText->get_content() << "\"" << std::endl;
	}
	else if(nodeComment) {
		print_indentation(indentation);
		std::cout << "comment = " << nodeComment->get_content() << std::endl;
	}
	else if(nodeContent) {
		print_indentation(indentation);
		std::cout << "content = " << nodeContent->get_content() << std::endl;
	}
	else if(const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(node)) {
		//A normal Element node:
		
		//line() works only for ElementNodes.
		print_indentation(indentation);
		std::cout << "     line = " << node->get_line() << std::endl;
		
		//Print attributes:
		const xmlpp::Element::AttributeList& attributes = nodeElement->get_attributes();
		for(xmlpp::Element::AttributeList::const_iterator iter = attributes.begin(); iter != attributes.end(); ++iter) {
			const xmlpp::Attribute* attribute = *iter;
			print_indentation(indentation);
			std::cout << "  Attribute " << attribute->get_name() << " = " << attribute->get_value() << std::endl;
		}
		const xmlpp::Attribute* attribute = nodeElement->get_attribute("title");
		if(attribute) {
		  std::cout << "title found: =" << attribute->get_value() << std::endl; 
		}
	}
	
	if(!nodeContent) {
		//Recurse through child nodes:
		
		for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter) {
			print_node(*iter, indentation + 2); //recursive
		}
	}
}


/*
void Personalizador::construir() {
	try {
		xmlpp::DomParser parser;
		parser.set_validate();
		// la linea de abajo es para que haga sustituciones de caracteres especiales
		parser.set_substitute_entities();
		parser.parse_file(nombreArchivo);
		if(parser) {
		  const xmlpp::Node* nodo = parser.get_document()->get_root_node(); //deleted by DomParser.
		  construir_desde_nodo(nodo);
		}
	} catch(const std::exception& ex) {
		std::cout << "error en personalizacion de cliente: " << ex.what() << std::endl;
	}
}
*/

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


    // Tab 3.1 con con TablaComun

    Tab* pTab3_2 = new Tab("Tab 3_2 - Tabla Comun");

    FiltradoresTab* fTab3_2 = new FiltradoresTab();
    fTab3_2->agregarEntrada("Vendedor");
    fTab3_2->agregarEntrada("Sucursal");
    while (fTab3_2->tieneFiltrosConsultantes())
        pTab3_2->agregarConsultante(fTab3_2->getFiltroConsultante());
    while (fTab3_2->tieneFiltrosNavegables())
        pTab3_2->agregarFiltroNavegable(fTab3_2->getFiltroNavegable());

    Panel* pPanelTorta3_2 = new Panel();

    FiltradoresPanel* fPanel3_2 = new FiltradoresPanel(*fTab3_2);
    fPanel3_2->agregarResultado("Vendedor");
    fPanel3_2->agregarResultado("Marca");
    //fPanel3_2->agregarResultado("Producto");
    fPanel3_2->agregarResultado(Organizacion::nombreHecho(0), "CONT");

    while (fPanel3_2->tieneFiltrosConsultantes())
        pTab3_2->agregarConsultante(fPanel3_2->getFiltroConsultante());
    while (fPanel3_2->tieneFiltrosNavegables())
        pTab3_2->agregarFiltroNavegable(fPanel3_2->getFiltroNavegable());

    //Grafico* pGraficoTorta3_2 = new GraficoDeTorta(*fPanel3_2);
    TablaComun* tablaComun = new TablaComun(*fPanel3_2);
    pTab3_2->agregarConsultante(tablaComun);
    pPanelTorta3_2->setContenido(*tablaComun);

    Gtk::HSeparator* sep3_2 = new Gtk::HSeparator();
    Gtk::Table* pTable3_2 = new Gtk::Table(1, 1, true);
    pTable3_2->attach(*pPanelTorta3_2, 0, 1, 0, 1);


    hijos.push_back(fTab3_2);
    hijos.push_back(fPanel3_2);
    hijos.push_back(tablaComun);
    hijos.push_back(pPanelTorta3_2);
    hijos.push_back(sep3_2);
    hijos.push_back(pTable3_2);

    pTab3_2->pack_start(*fTab3_2, false, false);
    pTab3_2->pack_start(*sep3_2, false, false);
    pTab3_2->pack_start(*pTable3_2, true, true);

    pTab3_2->informarFinCreacion();

    tabs.push_back(pTab3_2);

    // Tab 4 - Barras simple
    Tab* pTab4 = new Tab("Tab 4 - Barras simple");
    FiltradoresTab* fTab4 = new FiltradoresTab();
    while (fTab4->tieneFiltrosConsultantes())
        pTab4->agregarConsultante(fTab4->getFiltroConsultante());
    while (fTab4->tieneFiltrosNavegables())
        pTab4->agregarFiltroNavegable(fTab4->getFiltroNavegable());

    Panel* pPanelBarras4 = new Panel();
    FiltradoresPanel* fPanel4 = new FiltradoresPanel(*fTab4);
    fPanel4->agregarResultado("Vendedor");
    fPanel4->agregarResultado(Organizacion::nombreHecho(1), "CONT");
    while (fPanel4->tieneFiltrosConsultantes())
        pTab4->agregarConsultante(fPanel4->getFiltroConsultante());
    while (fPanel4->tieneFiltrosNavegables())
        pTab4->agregarFiltroNavegable(fPanel4->getFiltroNavegable());

    Grafico* pGraficoBarras4 = new GraficoDeBarras(*fPanel4);
    pTab4->agregarConsultante(pGraficoBarras4);
    pPanelBarras4->setContenido(*pGraficoBarras4);

    Gtk::HSeparator* sep4 = new Gtk::HSeparator();
    Gtk::Table* pTable4 = new Gtk::Table(1, 1, true);
    pTable4->attach(*pPanelBarras4, 0, 1, 0, 1);

    hijos.push_back(fTab4);
    hijos.push_back(fPanel4);
    hijos.push_back(pGraficoBarras4);
    hijos.push_back(pPanelBarras4);
    hijos.push_back(sep4);
    hijos.push_back(pTable4);

    pTab4->pack_start(*fTab4, false, false);
    pTab4->pack_start(*sep4, false, false);
    pTab4->pack_start(*pTable4, true, true);

    pTab4->informarFinCreacion();

    tabs.push_back(pTab4);

    // Tab 5 - test gráfico de torta simple con input
    Tab* pTab5 = new Tab("Tab 5 - Torta simple+input");
    FiltradoresTab* fTab5 = new FiltradoresTab();
    while (fTab5->tieneFiltrosConsultantes())
        pTab5->agregarConsultante(fTab5->getFiltroConsultante());
    while (fTab5->tieneFiltrosNavegables())
        pTab5->agregarFiltroNavegable(fTab5->getFiltroNavegable());

    Panel* pPanelTorta5 = new Panel();
    FiltradoresPanel* fPanel5 = new FiltradoresPanel(*fTab5);
    fPanel5->agregarEntrada("Vendedor");
    fPanel5->agregarResultado("Producto");
    fPanel5->agregarResultado(Organizacion::nombreHecho(0), "CONT");
    while (fPanel5->tieneFiltrosConsultantes())
        pTab5->agregarConsultante(fPanel5->getFiltroConsultante());
    while (fPanel5->tieneFiltrosNavegables())
        pTab5->agregarFiltroNavegable(fPanel5->getFiltroNavegable());

    Grafico* pGraficoTorta5 = new GraficoDeTorta(*fPanel5);
    pTab5->agregarConsultante(pGraficoTorta5);
    pPanelTorta5->setContenido(*pGraficoTorta5);

    Gtk::HSeparator* sep5 = new Gtk::HSeparator();
    Gtk::Table* pTable5 = new Gtk::Table(1, 1, true);
    pTable5->attach(*pPanelTorta5, 0, 1, 0, 1);

    hijos.push_back(fTab5);
    hijos.push_back(fPanel5);
    hijos.push_back(pGraficoTorta5);
    hijos.push_back(pPanelTorta5);
    hijos.push_back(sep5);
    hijos.push_back(pTable5);

    pTab5->pack_start(*fTab5, false, false);
    pTab5->pack_start(*sep5, false, false);
    pTab5->pack_start(*pTable5, true, true);

    pTab5->informarFinCreacion();

    tabs.push_back(pTab5);

    // Tab 6 - Barras simple con input
    Tab* pTab6 = new Tab("Tab 6 - Barras simple+input");
    FiltradoresTab* fTab6 = new FiltradoresTab();
    while (fTab6->tieneFiltrosConsultantes())
        pTab6->agregarConsultante(fTab6->getFiltroConsultante());
    while (fTab6->tieneFiltrosNavegables())
        pTab6->agregarFiltroNavegable(fTab6->getFiltroNavegable());

    Panel* pPanelBarras6 = new Panel();
    FiltradoresPanel* fPanel6 = new FiltradoresPanel(*fTab6);
    fPanel6->agregarEntrada("Sucursal");
    fPanel6->agregarResultado("Vendedor");
    fPanel6->agregarResultado(Organizacion::nombreHecho(1), "CONT");
    while (fPanel6->tieneFiltrosConsultantes())
        pTab6->agregarConsultante(fPanel6->getFiltroConsultante());
    while (fPanel6->tieneFiltrosNavegables())
        pTab6->agregarFiltroNavegable(fPanel6->getFiltroNavegable());

    Grafico* pGraficoBarras6 = new GraficoDeBarras(*fPanel6);
    pTab6->agregarConsultante(pGraficoBarras6);
    pPanelBarras6->setContenido(*pGraficoBarras6);

    Gtk::HSeparator* sep6 = new Gtk::HSeparator();
    Gtk::Table* pTable6 = new Gtk::Table(1, 1, true);
    pTable6->attach(*pPanelBarras6, 0, 1, 0, 1);

    hijos.push_back(fTab6);
    hijos.push_back(fPanel6);
    hijos.push_back(pGraficoBarras6);
    hijos.push_back(pPanelBarras6);
    hijos.push_back(sep6);
    hijos.push_back(pTable6);

    pTab6->pack_start(*fTab6, false, false);
    pTab6->pack_start(*sep6, false, false);
    pTab6->pack_start(*pTable6, true, true);

    pTab6->informarFinCreacion();

    tabs.push_back(pTab6);

    // Tab 7 - gráfico de torta con input e input tab
    Tab* pTab7 = new Tab("Tab 7 - Torta + input + inputTab");
    FiltradoresTab* fTab7 = new FiltradoresTab();
    fTab7->agregarEntrada("Sucursal");
    while (fTab7->tieneFiltrosConsultantes())
        pTab7->agregarConsultante(fTab7->getFiltroConsultante());
    while (fTab7->tieneFiltrosNavegables())
        pTab7->agregarFiltroNavegable(fTab7->getFiltroNavegable());

    Panel* pPanelTorta7 = new Panel();
    FiltradoresPanel* fPanel7 = new FiltradoresPanel(*fTab7);
    fPanel7->agregarEntrada("Vendedor");
    fPanel7->agregarResultado("Producto");
    fPanel7->agregarResultado(Organizacion::nombreHecho(0), "CONT");
    while (fPanel7->tieneFiltrosConsultantes())
        pTab7->agregarConsultante(fPanel7->getFiltroConsultante());
    while (fPanel7->tieneFiltrosNavegables())
        pTab7->agregarFiltroNavegable(fPanel7->getFiltroNavegable());

    Grafico* pGraficoTorta7 = new GraficoDeTorta(*fPanel7);
    pTab7->agregarConsultante(pGraficoTorta7);
    pPanelTorta7->setContenido(*pGraficoTorta7);

    Gtk::HSeparator* sep7 = new Gtk::HSeparator();
    Gtk::Table* pTable7 = new Gtk::Table(1, 1, true);
    pTable7->attach(*pPanelTorta7, 0, 1, 0, 1);

    hijos.push_back(fTab7);
    hijos.push_back(fPanel7);
    hijos.push_back(pGraficoTorta7);
    hijos.push_back(pPanelTorta7);
    hijos.push_back(sep7);
    hijos.push_back(pTable7);

    pTab7->pack_start(*fTab7, false, false);
    pTab7->pack_start(*sep7, false, false);
    pTab7->pack_start(*pTable7, true, true);

    pTab7->informarFinCreacion();

    tabs.push_back(pTab7);

    // Tab 8 - Barras con input e input tab
    Tab* pTab8 = new Tab("Tab 8 - Barras simple + input + inputTab");
    FiltradoresTab* fTab8 = new FiltradoresTab();
    fTab8->agregarEntrada("Producto");
    while (fTab8->tieneFiltrosConsultantes())
        pTab8->agregarConsultante(fTab8->getFiltroConsultante());
    while (fTab8->tieneFiltrosNavegables())
        pTab8->agregarFiltroNavegable(fTab8->getFiltroNavegable());

    Panel* pPanelBarras8 = new Panel();
    FiltradoresPanel* fPanel8 = new FiltradoresPanel(*fTab8);
    fPanel8->agregarEntrada("Sucursal");
    fPanel8->agregarResultado("Vendedor");
    fPanel8->agregarResultado(Organizacion::nombreHecho(1), "CONT");
    while (fPanel8->tieneFiltrosConsultantes())
        pTab8->agregarConsultante(fPanel8->getFiltroConsultante());
    while (fPanel8->tieneFiltrosNavegables())
        pTab8->agregarFiltroNavegable(fPanel8->getFiltroNavegable());

    Grafico* pGraficoBarras8 = new GraficoDeBarras(*fPanel8);
    pTab8->agregarConsultante(pGraficoBarras8);
    pPanelBarras8->setContenido(*pGraficoBarras8);

    Gtk::HSeparator* sep8 = new Gtk::HSeparator();
    Gtk::Table* pTable8 = new Gtk::Table(1, 1, true);
    pTable8->attach(*pPanelBarras8, 0, 1, 0, 1);

    hijos.push_back(fTab8);
    hijos.push_back(fPanel8);
    hijos.push_back(pGraficoBarras8);
    hijos.push_back(pPanelBarras8);
    hijos.push_back(sep8);
    hijos.push_back(pTable8);

    pTab8->pack_start(*fTab8, false, false);
    pTab8->pack_start(*sep8, false, false);
    pTab8->pack_start(*pTable8, true, true);

    pTab8->informarFinCreacion();

    tabs.push_back(pTab8);

    // Tab 9 - Torta y barras - test navegación
    Tab* pTab9 = new Tab("Tab 9 - Torta y barras + input - test navegación");
    FiltradoresTab* fTab9 = new FiltradoresTab();
    while (fTab9->tieneFiltrosConsultantes())
        pTab9->agregarConsultante(fTab9->getFiltroConsultante());
    while (fTab9->tieneFiltrosNavegables())
        pTab9->agregarFiltroNavegable(fTab9->getFiltroNavegable());

    Panel* pPanelTorta9 = new Panel();
    FiltradoresPanel* fPanel9 = new FiltradoresPanel(*fTab9);
    fPanel9->agregarEntrada("Sucursal");
    fPanel9->agregarResultado("Vendedor");
    fPanel9->agregarResultado(Organizacion::nombreHecho(0), "CONT");
    while (fPanel9->tieneFiltrosConsultantes())
        pTab9->agregarConsultante(fPanel9->getFiltroConsultante());
    while (fPanel9->tieneFiltrosNavegables())
        pTab9->agregarFiltroNavegable(fPanel9->getFiltroNavegable());

    Grafico* pGraficoTorta9 = new GraficoDeTorta(*fPanel9);
    pTab9->agregarConsultante(pGraficoTorta9);
    pPanelTorta9->setContenido(*pGraficoTorta9);

    Gtk::HSeparator* sep9 = new Gtk::HSeparator();

    Panel* pPanelBarras10 = new Panel();
    FiltradoresPanel* fPanel10 = new FiltradoresPanel(*fTab9);
    fPanel10->agregarResultado("Sucursal");
    fPanel10->agregarResultado(Organizacion::nombreHecho(0), "CONT");
    while (fPanel10->tieneFiltrosConsultantes())
        pTab9->agregarConsultante(fPanel10->getFiltroConsultante());
    while (fPanel10->tieneFiltrosNavegables())
        pTab9->agregarFiltroNavegable(fPanel10->getFiltroNavegable());

    Grafico* pGraficoBarras10 = new GraficoDeBarras(*fPanel10);
    pTab9->agregarConsultante(pGraficoBarras10);
    pPanelBarras10->setContenido(*pGraficoBarras10);

    Gtk::HSeparator* sep10 = new Gtk::HSeparator();

    Gtk::Table* pTable9 = new Gtk::Table(2, 1, true);
    pTable9->attach(*pPanelTorta9, 0, 1, 0, 1);
    pTable9->attach(*pPanelBarras10, 1, 2, 0, 1);

    hijos.push_back(fTab9);
    hijos.push_back(fPanel9);
    hijos.push_back(pPanelTorta9);
    hijos.push_back(sep9);
    hijos.push_back(fPanel10);
    hijos.push_back(pGraficoBarras10);
    hijos.push_back(pPanelBarras10);
    hijos.push_back(sep10);
    hijos.push_back(pTable9);

    pTab9->pack_start(*fTab9, false, false);
    pTab9->pack_start(*sep9, false, false);
    pTab9->pack_start(*pTable9, true, true);

    pTab9->informarFinCreacion();

    tabs.push_back(pTab9);


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
