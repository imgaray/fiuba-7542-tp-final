#include "Panel.h"
#include "Grafico.h"
#include "Filtrador.h"
#include "Respuesta.h"

Panel::Panel(Grafico& g, Filtrador& f) : grafico(g), filtrador(f) {
    pack_start(filtrador, false, false);
    scrWin.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    pViewport = new Gtk::Viewport(*scrWin.get_hadjustment(), *scrWin.get_vadjustment());
    pViewport->add(grafico);
    scrWin.add(*pViewport);
    add(scrWin);
}

Panel::~Panel() {
    delete pViewport;
}

void Panel::hacerConsulta() {
}

void procesarRespuesta(const Respuesta& rta) {
    // Para cuando esté conectado con el server
//    if (rta.huboError())
//        std::cout << "Algo se rompió" << std::endl;
//    else
//        consultantes[ID-ID_consultante]->algunMetodoParaRecibirRespuesta( :-) );

//    unsigned tt = rand() % 8 + 1;
//    double valor;
//    Glib::ustring nombres[9] = { "Migue", "Nacho", "Maria", "Micaela",
//        "Sebastian", "Sandra", "Pablo", "Gonzalo", "Julia" };
//    std::list< Hecho > datos;
//    for (unsigned i = 0; i < tt; ++i) {
//        valor = (rand() % 100 + 1) * 1.123456789;
//        datos.push_back(Hecho(nombres[i] , valor));
//    }
//
//    grafico.actualizarDatos(datos);
}

