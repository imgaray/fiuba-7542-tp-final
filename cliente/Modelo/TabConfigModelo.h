#ifndef TAB_CONFIG_MODELO_H
#define TAB_CONFIG_MODELO_H

#include <gtkmm/entry.h>
#include <gtkmm/spinbutton.h>

#define NOMBRE_TAB_POR_DEFECTO "Nueva pestaña"
#define MAX_GRILLA 99

class TabConfigModelo {
    public:
        TabConfigModelo();
        ~TabConfigModelo();

        void desconectar();
        void setEntryTabLabel(Gtk::Entry* pEntry);
        void setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                  Gtk::SpinButton* pCols);

        Glib::ustring getTabLabel() const;
        Glib::ustring getTabLabelNueva() const;
        void setTabLabelNuevaComoValida();
    private:
        /** modelo mismo */
        Glib::ustring tabLabel;
        unsigned filas, cols;
        unsigned min_fila, min_col;
        bool ocupacionesGrilla[MAX_GRILLA][MAX_GRILLA];

        /** conexiones a las señales de la vista */
        sigc::connection connectionEntryTabLabel;
        sigc::connection connectionSpinButtonFilas, connectionSpinButtonCols;

        /** signal handlers */
        void on_entry_tab_label_changed();
        void on_spinbutton_filas_value_changed();
        void on_spinbutton_cols_value_changed();

        /** referencias a la vista */
        Gtk::Entry* pEntryTabLabel;
        Gtk::SpinButton* pSpinButtonFilas;
        Gtk::SpinButton* pSpinButtonCols;
};

#endif  // TAB_CONFIG_MODELO_H

