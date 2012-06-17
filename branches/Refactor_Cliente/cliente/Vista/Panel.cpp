#include "Panel.h"

Panel::Panel() {
//    pack_start(filtrador, false, false);
    scrWin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    pViewport = new Gtk::Viewport(*scrWin.get_hadjustment(), *scrWin.get_vadjustment());
//    pViewport->add(grafico);
    scrWin.add(*pViewport);
    add(scrWin);
}

Panel::~Panel() {
    delete pViewport;
}

