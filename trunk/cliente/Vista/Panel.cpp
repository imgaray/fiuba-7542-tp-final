#include "Panel.h"
#include "Grafico.h"
#include "FiltradoresPanel.h"
#include "Respuesta.h"

Panel::Panel() {
    scrWin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    pViewport = new Gtk::Viewport(*scrWin.get_hadjustment(), *scrWin.get_vadjustment());
    scrWin.add(*pViewport);
}

Panel::~Panel() {
    delete pViewport;
}

void Panel::setContenido(Grafico& g) {
    pack_start(g.getFiltrador(), false, false);
    pViewport->add(g);
    add(scrWin);
}
