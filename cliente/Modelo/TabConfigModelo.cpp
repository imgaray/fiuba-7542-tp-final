#include "TabConfigModelo.h"
#include "PanelConfigModelo.h"
#include "AdminConfigObjManager.h"

TabConfigModelo::TabConfigModelo()
: ConfigModelo(NOMBRE_TAB_POR_DEFECTO),
  panelManager(NULL),
  pModeloPanel(NULL),
  pSpinButtonFilas(NULL), pSpinButtonCols(NULL) {
    filas = 1; cols = 1;
    min_fila = 1; min_col = 1;
    for (unsigned i = 0; i < MAX_GRILLA; ++i)
        for (unsigned j = 0; j < MAX_GRILLA; ++j)
            ocupacionesGrilla[i][j] = false;
}

TabConfigModelo::~TabConfigModelo() {
    desconectar();
}

sigc::signal< void, PanelConfigModelo* > TabConfigModelo::signal_panel_model_changed() {
    return _signal_panel_model_changed;
}

PanelConfigModelo* TabConfigModelo::getModeloPanel() const {
    return pModeloPanel;
}

void TabConfigModelo::setObjManagerPanel(Gtk::ComboBoxText* cbtext,
                                        Gtk::Button* pAceptar,
                                        Gtk::Button* pGuardarCambios,
                                        Gtk::Button* pEliminar
                                        ) {
    if (!panelManager) {
        panelManager = new AdminConfigObjManager(OBJ_PANEL,
                                                 cbtext,
                                                 pAceptar,
                                                 pGuardarCambios,
                                                 pEliminar,
                                                 NOMBRE_PANEL_POR_DEFECTO
                                                );
        on_panel_model_changed(panelManager->getModelo());
        panelManager->signal_model_changed().connect(sigc::mem_fun(*this,
            &TabConfigModelo::on_panel_model_changed));
    } else {
        panelManager->reconectar();

    }
}
#include <iostream>
void TabConfigModelo::desconectarDeHijo() {
    if (panelManager)
        panelManager->desconectar();

    if (pSpinButtonFilas) {
        connectionSpinButtonFilas.disconnect();
        pSpinButtonFilas = NULL;
    }
    if (pSpinButtonCols) {
        connectionSpinButtonCols.disconnect();
        pSpinButtonCols = NULL;
    }
}

void TabConfigModelo::on_panel_model_changed(ConfigModelo* m) {
    std::cout << "TabConfigModelo ( " << this << " ) recibida la señal de modelo nuevo ";
    PanelConfigModelo* mPanel = dynamic_cast< PanelConfigModelo* >(m);
    if (mPanel) {
        std::cout << "de panel: " << m << std::endl;
        std::cout << "TabConfigModelo ( " << this << " ) emitiendo señal panel_model_changed, parám: " << m << std::endl;
        pModeloPanel = mPanel;
        _signal_panel_model_changed.emit(mPanel);
    }
    else
        throw "Vista y modelo incompatibles";
}

void TabConfigModelo::setSpinButtonsGrilla(Gtk::SpinButton* pFilas,
                                           Gtk::SpinButton* pCols) {
    pSpinButtonFilas = pFilas;
    pSpinButtonCols = pCols;
    pSpinButtonFilas->set_value(filas);
    pSpinButtonCols->set_value(cols);
    pSpinButtonFilas->get_adjustment()->set_lower(min_fila);
    pSpinButtonCols->get_adjustment()->set_lower(min_col);

    connectionSpinButtonFilas = pSpinButtonFilas->signal_value_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_spinbutton_filas_value_changed));
    connectionSpinButtonCols = pSpinButtonCols->signal_value_changed().connect(
        sigc::mem_fun(*this, &TabConfigModelo::on_spinbutton_cols_value_changed));
}

void TabConfigModelo::on_spinbutton_filas_value_changed() {
    filas = pSpinButtonFilas->get_value_as_int();
}

void TabConfigModelo::on_spinbutton_cols_value_changed() {
    cols = pSpinButtonCols->get_value_as_int();
}
