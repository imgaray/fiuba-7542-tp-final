#ifndef PERSONALIZADOR_H
#define PERSONALIZADOR_H

#include <list>

class Tab;
class VentanaClienteDinamica;
class AdminConfigObjManager;

/** @class Personalizador
 * Clase intermedia entre el conjunto de objetos de configuración
 * (AdminConfigObjManager) y la VentanaClienteDinamica.
 *
 * Además de presentarle una interfaz limpia de estilo STL-container,
 * se encarga de la memoria reservada del heap de las configuraciones
 * anteriores, deprecadas, para eliminarlas todas juntas al cierre de la
 * aplicación.
 */
class Personalizador {
    public:
        /**
         * Constructor.
         */
        Personalizador();
        /**
         * Destructor. Libera toda la memoria de las tabs configuradas que ya
         * no están en uso.
         */
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
