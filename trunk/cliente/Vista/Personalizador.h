#ifndef PERSONALIZADOR_H
#define PERSONALIZADOR_H

#include <fstream>
#include <list>
#include <gtkmm/object.h>

class Tab;

class Personalizador {
    public:
        Personalizador();
        ~Personalizador();
        bool personalizarDesdeArchivo(const char* nombreArch);
        bool tieneSiguiente();
        Tab& siguiente();
    private:
        std::ifstream archivo;
        std::list< Tab* > tabs;
        std::list< Tab* >::iterator it;
        std::list< Gtk::Object* > hijos;
        void construir();
};
#endif  // PERSONALIZADOR_H
