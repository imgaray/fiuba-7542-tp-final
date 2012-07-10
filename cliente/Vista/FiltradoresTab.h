#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include "Filtradores.h"

/** @class FiltradoresTab
 * Implementación concreta de un conjunto de filtradores, el de las tabs.
 * Sólo admiten inputs, y se aplican a todo panel dentro de la pestaña.
 */
class FiltradoresTab : public Filtradores {
    public:
        FiltradoresTab();
        ~FiltradoresTab();

        void agregarEntrada(const std::string& entrada);
};

#endif  // FILTRADORES_TAB_H
