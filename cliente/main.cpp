#include "Cliente.h"
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Cliente c(argc, argv);
    c.run();  // Ponele correr() si querés, no me jode :P
    return 0;
}
