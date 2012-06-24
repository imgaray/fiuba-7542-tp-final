#ifndef TAB_CONFIG_MODELO_H
#define TAB_CONFIG_MODELO_H

#include <gtkmm/entry.h>

#define NOMBRE_TAB_POR_DEFECTO "Nueva pestaña"
#define MAX_GRILLA 99

class TabConfigVista;

class TabConfigModelo {
    public:
        TabConfigModelo();
        ~TabConfigModelo();

        void desconectar();
        void setEntryTabLabel(Gtk::Entry* pEntry);

        Glib::ustring getTabLabel() const;
    private:
        /** modelo mismo */
        Glib::ustring tabLabel;
        unsigned filas, cols;
        unsigned min_fila, min_col;
        bool ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];

        /** conexiones a las señales de la vista */
        sigc::connection connectionEntryTabLabel;

        /** signal handlers */
        void on_entry_tab_label_changed();

        /** referencias a la vista */
        Gtk::Entry* pEntryTabLabel;
};

#endif  // TAB_CONFIG_MODELO_H

