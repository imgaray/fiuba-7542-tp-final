#include "AdminConfigObjManager.h"
#include "TabConfigModelo.h"
#include "PanelConfigModelo.h"

AdminConfigObjManager::AdminConfigObjManager(t_Objeto _tipo,
                                             Gtk::ComboBoxText* cbtext,
                                             Gtk::Button* pAceptar,
                                             Gtk::Button* pGuardarCambios,
                                             Gtk::Button* pEliminar,
                                             const Glib::ustring& def)
: tipo(_tipo),
  nombre_por_defecto(def),
  pModeloActual(NULL),
  comboSelec(cbtext) {
    guardandoCambios = false;

    // botones
    botones[B_ACEPTAR] = pAceptar;
    connectionButtonAgregar = pAceptar->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_agregar_button_clicked));
    botones[B_GUARDAR] = pGuardarCambios;
    connectionButtonGuardar = pGuardarCambios->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_guardar_cambios_button_clicked));
    botones[B_ELIMINAR] = pEliminar;
    connectionButtonEliminar = pEliminar->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_eliminar_button_clicked));

    // combobox
    connectionCombobox = comboSelec->signal_changed().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_combo_selec_changed));

    pModeloActual = new_modelo();
    mapaConsultasConfiguradas[nombre_por_defecto] = pModeloActual;

    comboSelec->append_text(nombre_por_defecto);
    comboSelec->set_active(0);
}

AdminConfigObjManager::~AdminConfigObjManager() {
    // lo agrego por ser más simple y óptimo iterar sobre una lista que un mapa
    pModeloActual = mapaConsultasConfiguradas[nombre_por_defecto];
    consultasConfiguradas.push_back(pModeloActual);

    std::list< ConfigModelo* >::iterator it = consultasConfiguradas.begin();
    for ( ; it != consultasConfiguradas.end(); ++it) {
        pModeloActual = *it; // para evitar un warning del compilador
        delete pModeloActual;
    }
}

ConfigModelo* AdminConfigObjManager::getModelo() const {
    return pModeloActual;
}

sigc::signal< void, ConfigModelo* > AdminConfigObjManager::signal_model_changed() {
    return _signal_model_changed;
}

void  AdminConfigObjManager::desconectar() {
    connectionButtonAgregar.disconnect();
    connectionButtonGuardar.disconnect();
    connectionButtonEliminar.disconnect();
    connectionCombobox.disconnect();
    comboSelec->clear_items();
}

void  AdminConfigObjManager::reconectar() {
    // reconectar señales de botones
    connectionButtonAgregar = botones[B_ACEPTAR]->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_agregar_button_clicked));

    connectionButtonGuardar = botones[B_GUARDAR]->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_guardar_cambios_button_clicked));

    connectionButtonEliminar = botones[B_ELIMINAR]->signal_clicked().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_eliminar_button_clicked));

    // recargar todas las opciones al combobox
    comboSelec->append_text(nombre_por_defecto);
    std::list< ConfigModelo* >::const_iterator it = consultasConfiguradas.begin();
    for ( ; it != consultasConfiguradas.end(); ++it)
        comboSelec->append_text((*it)->getLabel());

    // reconectar la señal del combobox, y activar el actual
    connectionCombobox = comboSelec->signal_changed().connect(
        sigc::mem_fun(*this, &AdminConfigObjManager::on_combo_selec_changed));
    comboSelec->set_active_text(pModeloActual->getLabel());
}

#include <iostream>
void AdminConfigObjManager::on_agregar_button_clicked() {
    // Pedirle a ConfigModelo el título actual, verificar que no exista para
    // ver si se puede agregar. Si es válido, se agrega la entrada
    // mapaConsultasConfiguradas[título] = pModeloActual, y a la lista.
    // La entrada mapaConsultasConfiguradas[nombre_por_defecto] se pisa con
    // un modelo nuevo
    Glib::ustring label = pModeloActual->getLabelNueva();
    if (mapaConsultasConfiguradas.find(label) == mapaConsultasConfiguradas.end()) {
        pModeloActual->setLabelNuevaComoValida();
        mapaConsultasConfiguradas[label] = pModeloActual;
        consultasConfiguradas.push_back(pModeloActual);
        comboSelec->append_text(label);
        comboSelec->set_active_text(label);
        mapaConsultasConfiguradas[nombre_por_defecto] = new_modelo();
    }
}

void AdminConfigObjManager::on_guardar_cambios_button_clicked() {
    Glib::ustring labelNueva = pModeloActual->getLabelNueva();
    // si lo encuentra en el mapa, es porque ya existe y no es válido
    if (mapaConsultasConfiguradas.find(labelNueva) != mapaConsultasConfiguradas.end())
        return;
    if (labelNueva == nombre_por_defecto)
        return;

    guardandoCambios = true;
        int pos = comboSelec->get_active_row_number();
        Glib::ustring labelVieja = pModeloActual->getLabel();
        comboSelec->remove_text(labelVieja);
        mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(labelVieja));
        mapaConsultasConfiguradas[labelNueva] = pModeloActual;
        pModeloActual->setLabelNuevaComoValida();
        comboSelec->insert_text(pos, labelNueva);
    guardandoCambios = false;
    comboSelec->set_active(pos);

}

void AdminConfigObjManager::on_eliminar_button_clicked() {
    // eliminar modelo seleccionado, remover del mapa, la lista y del combobox
    // busco por el label viejo porque es con el que está en el mapa hasta que se aplican los cambios

    Glib::ustring label = pModeloActual->getLabel();
    mapaConsultasConfiguradas.erase(mapaConsultasConfiguradas.find(label));

    std::list< ConfigModelo* >::iterator it = consultasConfiguradas.begin();
    bool encontrado = false;
    while (!encontrado && it != consultasConfiguradas.end())
        encontrado = (*(it++)) == pModeloActual;

    if (encontrado)
        consultasConfiguradas.erase(--it);

    ConfigModelo* bckup = pModeloActual;
    guardandoCambios = true;
        int pos = comboSelec->get_active_row_number();
        comboSelec->remove_text(label);
    guardandoCambios = false;
    comboSelec->set_active(pos-1);
    delete bckup;
}

void AdminConfigObjManager::on_combo_selec_changed() {
    if (guardandoCambios)
        return;
    Glib::ustring label = comboSelec->get_active_text();
    if (label == nombre_por_defecto) {
        botones[B_ACEPTAR]->show();
        botones[B_GUARDAR]->hide();
        botones[B_ELIMINAR]->hide();
    } else {
        botones[B_ACEPTAR]->hide();
        botones[B_GUARDAR]->show();
        botones[B_ELIMINAR]->show();
    }

    pModeloActual = mapaConsultasConfiguradas[label];

    std::cout << "AdminConfigObjManager( " <<this << " ) emitiendo modelo ";
    if (tipo == OBJ_TAB)
        std::cout << "tab";
    else
        std::cout << "panel";
    std::cout << " nuevo: " << pModeloActual << std::endl;
    _signal_model_changed.emit(pModeloActual);
}

ConfigModelo* AdminConfigObjManager::new_modelo() {
    switch (tipo) {
        case OBJ_TAB:   return new TabConfigModelo();
        case OBJ_PANEL: return new PanelConfigModelo();
        default: return NULL;
    }
}
