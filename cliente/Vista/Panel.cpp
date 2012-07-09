#include "Panel.h"
#include "Grafico.h"
#include "Tabla.h" // linea descomentada
#include "FiltradoresPanel.h"
#include "Respuesta.h"

Panel::Panel(const Glib::ustring& label) : Gtk::Frame(label) {
    set_label_align(0.5);
    add(box);
    scrWin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    pViewport = manage(new Gtk::Viewport(*scrWin.get_hadjustment(),
                                         *scrWin.get_vadjustment()));
    scrWin.add(*pViewport);
}

Panel::~Panel() {}

void Panel::setContenido(Grafico& g) {
    consultante = &g;
    box.pack_start(*(g.getFiltrador()), false, false);
    pViewport->add(g);
    box.add(scrWin);
}

void Panel::setContenido(Tabla& t) {
    consultante = &t;
    box.pack_start(*(t.getFiltrador()), false, false);
    pViewport->add(t);
    box.add(scrWin);
}

Consultante* Panel::getConsultante() {
    return consultante;
}
