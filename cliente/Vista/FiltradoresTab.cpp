#include "FiltradoresTab.h"
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinner.h>
#include <gtkmm/separator.h>
#include "Organizacion.h"
#include "ExcepcionFiltradorMalConstruido.h"
#include "Filtrador.h"
#include "FiltradorInputDimension.h"
#include "FiltradorInputFecha.h"
#include "FiltradorInputHecho.h"

#define EXCEP_MSJ_INPUT_MAL     "El campo solicitado para el input no es dimensión ni hecho"

//
///** @todo conectar las señales */
//Filtrador::Filtrador(const Filtros& filt, const Entradas& entr)
//: filtros(filt), entradasTab(entr) {
//    Gtk::HBox* cont;
//    Gtk::Label* dim;
//    Gtk::Label* val;
//    Gtk::ComboBoxText* cbText;
//    Gtk::VSeparator* sep;
//    Gtk::Spinner* eyecandy;
//    Filtros::iterator itFiltros = filtros.begin();
//    while (itFiltros != filtros.end()) {
//        cont = new Gtk::HBox();
//        dim = new Gtk::Label(itFiltros->first);
//        sep = new Gtk::VSeparator();
//        val = new Gtk::Label(itFiltros->second);
//        /** @todo poner esto más elegante... */
//        if (itFiltros == filtros.begin()) {
//            eyecandy = new Gtk::Spinner();
//            cont->pack_start(*eyecandy, false, false);
//            widgets.push_back(eyecandy);
//        }
//        cont->pack_end(*val, false, false);
////        cont->pack_start(*val, false, false);
//        cont->add(*dim);
//        cont->add(*sep);
//
//        widgets.push_back(cont);
//        widgets.push_back(dim);
//        widgets.push_back(sep);
//        widgets.push_back(val);
//
//        if (itFiltros == filtros.begin())
//            pack_start(*cont, false, false);
//        else
//            add(*cont);
//        ++itFiltros;
//    }
//
//    Entradas::iterator itEntradas = entradasTab.begin();
//    while (itEntradas != entradasTab.end()) {
//        cont = new Gtk::HBox();
//        dim = new Gtk::Label(itEntradas->first);
//        sep = new Gtk::VSeparator();
//        cbText = new Gtk::ComboBoxText();
//        cbText->append_text("Test comboboxtext");
//        cbText->append_text("Test comboboxtext2");
//        /** @todo poner esto más elegante... */
//        if (itEntradas == entradasTab.begin()) {
//            eyecandy = new Gtk::Spinner();
//            cont->pack_start(*eyecandy, false, false);
//            widgets.push_back(eyecandy);
//        }
//        cont->pack_end(*cbText, false, false);
//        cont->add(*dim);
//        cont->add(*sep);
//
//        widgets.push_back(cont);
//        widgets.push_back(dim);
//        widgets.push_back(sep);
//        widgets.push_back(cbText);
//
//        if (itEntradas == entradasTab.begin())
//            pack_start(*cont, false, false);
//        else
//            add(*cont);
//        ++itEntradas;
//    }
//
//}
//
//Filtrador::Filtrador(const Filtrador& filt, const Entradas& entrPanel) :
//entradasPanel(entrPanel) {
//    Gtk::HBox* cont;
//    Gtk::Label* dim;
//    Gtk::ComboBoxText* cbText;
//    Gtk::VSeparator* sep;
//    Gtk::Spinner* eyecandy;
//    Entradas::iterator itEntradas = entradasPanel.begin();
//    while (itEntradas != entradasPanel.end()) {
//        cont = new Gtk::HBox();
//        dim = new Gtk::Label(itEntradas->first);
//        sep = new Gtk::VSeparator();
//        cbText = new Gtk::ComboBoxText();
//        cbText->append_text("Test comboboxtext");
//        cbText->append_text("Test comboboxtext2");
//        /** @todo poner esto más elegante... */
//        if (itEntradas == entradasPanel.begin()) {
//            eyecandy = new Gtk::Spinner();
//            cont->pack_start(*eyecandy, false, false);
//            widgets.push_back(eyecandy);
//        }
//        cont->pack_end(*cbText, false, false);
//        cont->add(*dim);
//        cont->add(*sep);
//
//        widgets.push_back(cont);
//        widgets.push_back(dim);
//        widgets.push_back(sep);
//        widgets.push_back(cbText);
//
//        add(*cont);
//        ++itEntradas;
//    }
//}
//
//Filtrador::~Filtrador() {
//    std::list< Gtk::Widget* >::iterator it = widgets.begin();
//    for ( ; it != widgets.end(); ++it)
//        delete *it;
//}

FiltradoresTab::FiltradoresTab() {}

FiltradoresTab::~FiltradoresTab() {
    std::list< Gtk::Widget* >::iterator it = widgets.begin();
    for ( ; it != widgets.end(); ++it)
        delete *it;
}

void FiltradoresTab::agregarEntrada(const std::string& entrada) {
    Filtrador* f;
    try {
        if (Organizacion::esDimension(entrada)) {
            if (Organizacion::esDimensionEspecial(entrada))
                f = new FiltradorInputFecha(entrada);
            else {
                f = new FiltradorInputDimension(entrada, this);
                    std::cout << "        Pft agregó un hijo (Cfid: " << f << ")" << std::endl;
            }
        } else {
            if (Organizacion::esHecho(entrada))
                f = new FiltradorInputHecho(entrada);
            else
                throw ExcepcionFiltradorMalConstruido(EXCEP_MSJ_INPUT_MAL);
        }
        add(*f);
        widgets.push_back(f);
    }
    catch (const ExcepcionFiltradorMalConstruido& e) {
        std::cout << e.what() << std::endl;
    }
}
