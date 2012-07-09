#ifndef FILTRADORES_TAB_H
#define FILTRADORES_TAB_H

#include "Filtradores.h"

class FiltradoresTab : public Filtradores {
    public:
        FiltradoresTab();
        ~FiltradoresTab();

        void agregarEntrada(const std::string& entrada);
};

#endif  // FILTRADORES_TAB_H
