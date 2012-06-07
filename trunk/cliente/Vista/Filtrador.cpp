#include "Filtrador.h"
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/spinner.h>
#include <gtkmm/separator.h>

/** @todo conectar las señales */
Filtrador::Filtrador(const Filtros& filt, const Entradas& entr)
: filtros(filt), entradas(entr) {
    Gtk::HBox* cont;
    Gtk::Label* dim;
    Gtk::Label* val;
    Gtk::ComboBoxText* cbText;
    Gtk::VSeparator* sep;
    Gtk::Spinner* eyecandy;
    Filtros::iterator itFiltros = filtros.begin();
    while (itFiltros != filtros.end()) {
        cont = new Gtk::HBox();
        dim = new Gtk::Label(itFiltros->first);
        sep = new Gtk::VSeparator();
        val = new Gtk::Label(itFiltros->second);
        /** @todo poner esto más elegante... */
        if (itFiltros == filtros.begin()) {
            eyecandy = new Gtk::Spinner();
            cont->pack_start(*eyecandy, false, false);
            widgets.push_back(eyecandy);
        }
        cont->pack_end(*dim, false, false);
        cont->add(*sep);
        cont->add(*val);

        widgets.push_back(cont);
        widgets.push_back(dim);
        widgets.push_back(sep);
        widgets.push_back(val);

        if (itFiltros == filtros.begin())
            pack_start(*cont, false, false);
        else
            add(*cont);
        ++itFiltros;
    }

    Entradas::iterator itEntradas = entradas.begin();
    while (itEntradas != entradas.end()) {
        cont = new Gtk::HBox();
        dim = new Gtk::Label(itEntradas->first);
        sep = new Gtk::VSeparator();
        cbText = new Gtk::ComboBoxText();
        cbText->append_text("Test comboboxtext");
        cbText->append_text("Test comboboxtext2");
        /** @todo poner esto más elegante... */
        if (itEntradas == entradas.begin()) {
            eyecandy = new Gtk::Spinner();
            cont->pack_start(*eyecandy, false, false);
            widgets.push_back(eyecandy);
        }
        cont->pack_end(*dim, false, false);
        cont->add(*sep);
        cont->add(*cbText);

        widgets.push_back(cont);
        widgets.push_back(dim);
        widgets.push_back(sep);
        widgets.push_back(cbText);

        add(*cont);
        ++itEntradas;
    }

}

Filtrador::~Filtrador() {
    std::list< Gtk::Widget* >::iterator it = widgets.begin();
    for ( ; it != widgets.end(); ++it)
        delete *it;
}
