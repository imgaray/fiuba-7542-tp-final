#ifndef PERSONALIZADOR_H
#define PERSONALIZADOR_H

#include <list>

class Tab;
class VentanaClienteDinamica;
class AdminConfigObjManager;

class Personalizador {
    public:
        Personalizador();
        ~Personalizador();
        void construir(AdminConfigObjManager* tabManager);
        bool tieneSiguiente() const;
        Tab& siguiente();
    private:
        std::list< Tab* > tabs;
        std::list< Tab* >::iterator it;
        std::list< Tab* > tabsViejas;  // acá van las que están en desuso, para eliminarlas todas de un saque en el destructor
        void deleteTabs();  // delete tabsViejas
        void deprecateTabs();  // manda las tabs actuales a la lista de viejas
};
#endif  // PERSONALIZADOR_H
