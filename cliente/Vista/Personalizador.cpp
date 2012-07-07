#include <gtkmm/separator.h>
#include <gtkmm/table.h>
#include <gtkmm/adjustment.h>
#include "Personalizador.h"
#include "Grafico.h"
#include "GraficoDeBarras.h"
#include "GraficoDeTorta.h"
#include "Tab.h"
#include "Panel.h"
#include "FiltradoresPanel.h"
#include "Organizacion.h"
#include "VentanaClienteDinamica.h"
#include "TablaComun.h"
#include "TablaPivote.h"
#include "AdminConfigObjManager.h"
#include "TabConfigModelo.h"

#include <iostream>

Personalizador::Personalizador() {
    Organizacion::cargarDefiniciones();
}

Personalizador::~Personalizador() {
    deprecateTabs();
    deleteTabs();
}

void Personalizador::deleteTabs() {
    it = tabsViejas.begin();
    for ( ; it != tabsViejas.end(); ++it)
        delete *it;
}
void Personalizador::deprecateTabs() {
    tabsViejas.splice(tabsViejas.end(), tabs);
}

bool Personalizador::tieneSiguiente() const {
    return it != tabs.end();
}

Tab& Personalizador::siguiente() {
    return **it++;
}

void Personalizador::construir(AdminConfigObjManager* tabManager) {
    deprecateTabs();
    std::list< TabConfigModelo* > tabsConfig(tabManager->getModelosComoTabs());

    std::list< TabConfigModelo* >::iterator itConfig = tabsConfig.begin();
    for ( ; itConfig != tabsConfig.end(); ++itConfig) {
        tabs.push_back((*itConfig)->concretarConfig());
    }
    it = tabs.begin();
}
