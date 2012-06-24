#include "TabConfigVista.h"
#include "ExcepcionArchivoGladeCorrupto.h"
#include "TabConfigModelo.h"

#define ENTRY_TAB_LABEL "entryTabLabel"

TabConfigVista::TabConfigVista(BaseObjectType* cobject,
                       const Glib::RefPtr< Gtk::Builder >& _builder)
: Gtk::Table(cobject), builder(_builder), pModelo(NULL) {
    builder->get_widget(ENTRY_TAB_LABEL, pEntryTabLabel);
    if (!pEntryTabLabel)
        throw ExcepcionArchivoGladeCorrupto(ENTRY_TAB_LABEL);

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
}


Glib::ustring TabConfigVista::getTabLabel() const {
    if (pModelo)
        return pModelo->getTabLabel();
    else
        return "";
}

