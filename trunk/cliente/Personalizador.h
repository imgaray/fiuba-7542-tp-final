#ifndef PERSONALIZADOR_H
#define PERSONALIZADOR_H

#include <fstream>
#include <list>
#include <glibmm/ustring.h>
#include <gtkmm/table.h>
//#include "Tab.h"

class Personalizador {
    public:
        Personalizador();
        ~Personalizador();
        bool personalizarDesdeArchivo(const char* nombreArch);
        bool tieneSiguiente();
        Gtk::Table& siguiente();
    private:
        std::ifstream archivo;
        std::list< Gtk::Table* > tabs;
        std::list< Gtk::Table* >::iterator it;
        std::list< Gtk::Widget* > hijos;
        void construir();
};
#endif  // PERSONALIZADOR_H
