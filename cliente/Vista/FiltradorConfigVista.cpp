#include "FiltradorConfigVista.h"
#include "FiltradorConfigModelo.h"
#include <gtkmm/enums.h>

#define LABEL_DIM "Dimensión o hecho: "
#define ELIMINAR_STOCK "gtk-no"

FiltradorConfigVista::FiltradorConfigVista(FiltradorConfigModelo* pModelo)
: labelDim(LABEL_DIM),
  idBotonEliminar(ELIMINAR_STOCK) {
    filtConfigBox.pack_start(labelDim, false, false);
    filtConfigBox.pack_start(comboDimension, false, false);
    filtConfigBox.pack_start(comboFecha, false, false);
    filtConfigBox.pack_start(comboHecho, false, false);
    filtConfigBox.pack_start(entryExtra, false, false);

    botonEliminar.set_stock_id(idBotonEliminar);
    tools.append(botonEliminar);
    tools.set_show_arrow(false);
    tools.set_icon_size(Gtk::IconSize(1));

    pack_start(filtConfigBox, true, true);
    pack_end(tools, false, false);
    show_all();

    pModelo->setVista(&comboDimension, &comboFecha, &comboHecho,
                      &entryExtra,
                      &botonEliminar);
}

FiltradorConfigVista::~FiltradorConfigVista() {}
