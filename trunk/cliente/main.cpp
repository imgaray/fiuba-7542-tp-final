#include "Vista/Cliente.h"
#include <gtkmm/main.h>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Cliente c(argc, argv);
    c.run();
    return 0;
}

