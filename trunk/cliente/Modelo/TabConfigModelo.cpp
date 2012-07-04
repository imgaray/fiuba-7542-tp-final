#include "TabConfigModelo.h"
#include "PanelConfigModelo.h"
#include "AdminConfigObjManager.h"
#include "FiltradorConfigManager.h"
#include "Organizacion.h"

TabConfigModelo::TabConfigModelo()
: ConfigModelo(NOMBRE_TAB_POR_DEFECTO),
  inputsManager(NULL),
  pSpinButtonFilas(NULL), pSpinButtonCols(NULL),
  panelManager(NULL),
  pModeloPanel(NULL) {
    filas = 1; cols = 1;
    min_fila = 1; min_col = 1;
    for (unsigned i = 0; i < MAX_GRILLA; ++i)
        for (unsigned j = 0; j < MAX_GRILLA; ++j)
            ocupacionesGrilla[i][j] = NULL;
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
        panelManager->signal_model_saved().connect(sigc::mem_fun(*this,
            &TabConfigModelo::on_panel_model_saved));
        panelManager->signal_model_deleted().connect(sigc::mem_fun(*this,
            &TabConfigModelo::on_panel_model_deleted));
    } else {
        panelManager->reconectar();
    }
}

void TabConfigModelo::setInputsHandlers(const filtradoresHandlers& handlers) {
    if (!inputsManager) {
        inputsManager = new FiltradorConfigManager(FILT_INPUT, handlers);

//        on_panel_model_changed(panelManager->getModelo());
//        panelManager->signal_model_changed().connect(sigc::mem_fun(*this,
//            &TabConfigModelo::on_panel_model_changed));
//        panelManager->signal_model_saved().connect(sigc::mem_fun(*this,
//            &TabConfigModelo::on_panel_model_saved));
//        panelManager->signal_model_deleted().connect(sigc::mem_fun(*this,
//            &TabConfigModelo::on_panel_model_deleted));
    } else {
        inputsManager->reconectar();
    }
}

#include <iostream>
void TabConfigModelo::desconectarDeHijo() {
    if (panelManager)
        panelManager->desconectar();
    if (inputsManager)
        inputsManager->desconectar();

    desconectar(connectionSpinButtonFilas, pSpinButtonFilas);
    desconectar(connectionSpinButtonCols, pSpinButtonCols);
    desconectar(connectionPanelPosicion, pModeloPanel);
}

void TabConfigModelo::ocuparGrilla(PanelConfigModelo* pModelo) {
//    imprimirGrilla();

    unsigned desdeFila, hastaFila;
    unsigned desdeCol, hastaCol;
    pModelo->getPosicion(desdeFila, hastaFila, desdeCol, hastaCol);

    on_panel_solicita_validacion(pModelo,
                                 desdeFila, hastaFila,
                                 desdeCol, hastaCol);

    for (unsigned i = desdeFila; i < hastaFila; ++i)
        for (unsigned j = desdeCol; j < hastaCol; ++j)
            ocupacionesGrilla[i][j] = pModelo;

//    imprimirGrilla();
}

void TabConfigModelo::desocuparGrilla(PanelConfigModelo* pModelo) {
//    imprimirGrilla();

    for (unsigned i = 0; i < filas; ++i)
        for (unsigned j = 0; j < cols; ++j)
            if (ocupacionesGrilla[i][j] == pModelo)
                ocupacionesGrilla[i][j] = NULL;

//    imprimirGrilla();
}

void TabConfigModelo::on_panel_model_changed(ConfigModelo* m) {
    PanelConfigModelo* mPanel = dynamic_cast< PanelConfigModelo* >(m);
    if (mPanel) {
        pModeloPanel = mPanel;
        ocuparGrilla(mPanel);
        connectionPanelPosicion = pModeloPanel->signal_posicion_changed().connect(
            sigc::mem_fun(*this, &TabConfigModelo::on_panel_solicita_validacion));
        _signal_panel_model_changed.emit(mPanel);
    }
    else
        throw "Vista y modelo incompatibles";
}

void TabConfigModelo::on_panel_model_saved(ConfigModelo* m) {
//    std::cout << "TabConfigModelo ( " << this << " ) recibida la señal de modelo nuevo ";
    PanelConfigModelo* mPanel = dynamic_cast< PanelConfigModelo* >(m);
    if (mPanel) {
        desocuparGrilla(mPanel);
        ocuparGrilla(mPanel);
    }
    else
        throw "Vista y modelo incompatibles";
}

void TabConfigModelo::on_panel_model_deleted(ConfigModelo* m) {
    PanelConfigModelo* mPanel = dynamic_cast< PanelConfigModelo* >(m);
    if (mPanel)
        desocuparGrilla(mPanel);
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
    unsigned filasNueva = pSpinButtonFilas->get_value_as_int();
    if (filasNueva >= min_fila)
        filas = filasNueva;
    else
        pSpinButtonFilas->set_value(min_fila);
}

void TabConfigModelo::on_spinbutton_cols_value_changed() {
    unsigned colsNueva = pSpinButtonCols->get_value_as_int();
    if (colsNueva >= min_col)
        cols = colsNueva;
    else
        pSpinButtonFilas->set_value(min_col);
}

void TabConfigModelo::on_panel_solicita_validacion(PanelConfigModelo* pPanel,
                                                   int desdeFila,
                                                   int hastaFila,
                                                   int desdeCol,
                                                   int hastaCol) {
//
//    for (int ii = 0; ii < filas; ++ii) {
//        for (int ji = 0; ji < cols; ++ji)
//            if (ocupacionesGrilla[ii][ji])
//                if (ocupacionesGrilla[ii][ji] == pPanel)
//                    std::cout << "=";
//                else
//                    std::cout << "!";
//            else
//                std::cout << ".";
//        std::cout << std::endl;
//    }

    bool ocupado = hastaFila > filas || hastaCol > cols;
    int i = desdeFila;
    int j = desdeCol;
    while (!ocupado && i < hastaFila) {
        while (!ocupado && j < hastaCol) {
            if (ocupacionesGrilla[i][j])
                ocupado = ocupacionesGrilla[i][j] != pPanel;
            ++j;
        }
        j = desdeCol;
        ++i;
    }

//    if (!ocupado)
//        for (i = desdeFila; i < hastaFila; ++i)
//            for (j = desdeCol; j < hastaCol; ++j)
//                ocupacionesGrilla[i][j] = pPanel;

//    std::cout << "Nuevo estado de la grilla: " << std::endl;
//    for (int ii = 0; ii < filas; ++ii) {
//        for (int ji = 0; ji < cols; ++ji)
//            if (ocupacionesGrilla[ii][ji])
//                if (ocupacionesGrilla[ii][ji] == pPanel)
//                    std::cout << "=";
//                else
//                    std::cout << "!";
//            else
//                std::cout << ".";
//        std::cout << std::endl;
//    }
    pModeloPanel->setPosicionNuevaComoValida(!ocupado);
}

void TabConfigModelo::imprimirGrilla() {
    std::cout << "Estado de la grilla" << std::endl;
    for (unsigned i = 0; i < filas; ++i) {
        for (unsigned j = 0; j < cols; ++j)
            if (ocupacionesGrilla[i][j])
                std::cout << "x";
            else
                std::cout << ".";
        std::cout << std::endl;
    }
}
