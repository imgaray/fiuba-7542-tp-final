#include "TabConfigVista.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"

#define ENTRY_TAB_LABEL "entryTabLabel"
#define SPINBUTTON_FILAS "spinbuttonFilas"
#define SPINBUTTON_COLS "spinbuttonCols"

TabConfigVista::TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Table(cobject), builder(_builder), pModelo(NULL) {
    builder->get_widget(ENTRY_TAB_LABEL, pEntryTabLabel);
    if (!pEntryTabLabel)
        throw ExcepcionArchivoGladeCorrupto(ENTRY_TAB_LABEL);

    builder->get_widget(SPINBUTTON_FILAS, pSpinButtonFilas);
    if (!pSpinButtonFilas)
        throw ExcepcionArchivoGladeCorrupto(SPINBUTTON_FILAS);

    builder->get_widget(SPINBUTTON_COLS, pSpinButtonCols);
    if (!pSpinButtonCols)
        throw ExcepcionArchivoGladeCorrupto(SPINBUTTON_COLS);

}

TabConfigVista::~TabConfigVista() {

}

#include <iostream>
void TabConfigVista::setModelo(TabConfigModelo* pModeloNuevo) {
    if (pModelo == pModeloNuevo)
        return;

    if (pModelo)
        pModelo->desconectar();

    std::cout << "Conectando modelo nuevo (@todo)" << std::endl;
    pModelo = pModeloNuevo;
    pModelo->setEntryTabLabel(pEntryTabLabel);
    pModelo->setSpinButtonsGrilla(pSpinButtonFilas, pSpinButtonCols);
}


