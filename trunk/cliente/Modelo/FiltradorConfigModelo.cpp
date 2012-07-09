#include "FiltradorConfigModelo.h"
#include "Organizacion.h"
#include "FiltradorHelper.h"


#define NOMBRE_NODO "Filtrador_Config_Modelo"
#define ATR_CAMPO "atr_campo"
#define ATR_VALOR_CAMPO "atr_valor_campo"
#define ATR_CAMPO_AUX "atr_campo_aux"



FiltradorConfigModelo::FiltradorConfigModelo(unsigned _ID,
                            const std::list< std::string >& _camposDisponibles)
: comboDimension(NULL), comboFecha(NULL), comboHecho(NULL),
  entryExtra(NULL),
  botonEliminar(NULL),
  ID(_ID),
  camposDisponibles(_camposDisponibles) {

}

FiltradorConfigModelo::~FiltradorConfigModelo() {}

void FiltradorConfigModelo::setVista(Gtk::ComboBoxText* _comboDimension,
                                     Gtk::ComboBoxText* _comboFecha,
                                     Gtk::ComboBoxText* _comboHecho,
                                     Gtk::Entry* _entryExtra,
                                     Gtk::ToolButton* _botonEliminar) {
    setComboDimension(_comboDimension);
    setComboFecha(_comboFecha);
    setComboHecho(_comboHecho);
    setEntryExtra(_entryExtra);
    setBotonEliminar(_botonEliminar);
    comboDimension->set_active(0);
    especializarVista();
}

unsigned FiltradorConfigModelo::getID() const {
    return ID;
}

void FiltradorConfigModelo::actualizarCampos(const Glib::ustring& remover,
                                             const Glib::ustring& agregar) {
    if (remover != "" && remover != campoSeleccNuevo)
        comboDimension->remove_text(remover);
    if (agregar != "" && agregar != campoSelecc)
        comboDimension->insert_text(Organizacion::indiceDeCampo(agregar),
                                    agregar);
}

void FiltradorConfigModelo::setComboDimension(Gtk::ComboBoxText* comboDim) {
    comboDimension = comboDim;
    comboDimension->clear_items();
    std::list< std::string >::const_iterator it = camposDisponibles.begin();
    for ( ; it != camposDisponibles.end(); ++it)
        comboDimension->append_text(*it);

    comboDimension->signal_changed().connect(sigc::mem_fun(*this,
        &FiltradorConfigModelo::on_combo_dimension_changed));
}

void FiltradorConfigModelo::setComboFecha(Gtk::ComboBoxText* _comboFecha) {
    comboFecha = _comboFecha;

    FiltradorHelper::getInstancia().popularComboFecha(comboFecha);

    comboFecha->signal_changed().connect(sigc::bind< Gtk::ComboBoxText* >(
        sigc::mem_fun(*this, &FiltradorConfigModelo::on_combo_aux_changed),
        comboFecha));

    comboFecha->set_active(0);
}

void FiltradorConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;

    FiltradorHelper::getInstancia().popularComboHechoInput(comboHecho);
    conectarComboHecho();

    comboHecho->set_active(0);
}

void FiltradorConfigModelo::conectarComboHecho() {
    comboHecho->signal_changed().connect(sigc::bind< Gtk::ComboBoxText* >(
        sigc::mem_fun(*this, &FiltradorConfigModelo::on_combo_aux_changed),
        comboHecho));
}

void FiltradorConfigModelo::setEntryExtra(Gtk::Entry* _entryExtra) {
    entryExtra = _entryExtra;
    entryExtra->set_text("");
}

void FiltradorConfigModelo::setBotonEliminar(Gtk::ToolButton* _botonEliminar) {
    botonEliminar = _botonEliminar;
    botonEliminar->signal_clicked().connect(sigc::mem_fun(*this,
        &FiltradorConfigModelo::on_boton_eliminar_clicked));
}

sigc::signal< void, unsigned > FiltradorConfigModelo::signal_delete_filtrador() {
    return _signal_delete_filtrador;
}

sigc::signal< void, Glib::ustring, Glib::ustring >
    FiltradorConfigModelo::signal_campo_changed() {
    return _signal_campo_changed;
}

void FiltradorConfigModelo::on_combo_aux_changed(Gtk::ComboBoxText* pCombo) {
    _campoAux = pCombo->get_active_text();
}

void FiltradorConfigModelo::on_boton_eliminar_clicked() {
    _signal_campo_changed.emit(campoSelecc, "");
    _signal_delete_filtrador.emit(ID);
}

NodoXml FiltradorConfigModelo::serializar() {
	NodoXml nodo(NOMBRE_NODO);


	// @todo ver si necesario sacar esta linea..
	_campoAux = comboHecho->get_active_text();

	nodo.SetAttribute(ATR_CAMPO, campoSelecc.c_str());
	nodo.SetAttribute(ATR_VALOR_CAMPO, _valorCampo.c_str());
	nodo.SetAttribute(ATR_CAMPO_AUX, _campoAux.c_str());

	return nodo;
}

void FiltradorConfigModelo::deserializar(const NodoXml& nodo) {

	if (nodo.Attribute(ATR_CAMPO)) {
		campoSeleccNuevo = nodo.Attribute(ATR_CAMPO);
	}
	else {
		throw ErrorSerializacionXML();
	}

	if (nodo.Attribute(ATR_VALOR_CAMPO)) {
		_valorCampo = nodo.Attribute(ATR_VALOR_CAMPO);
	}
	else {
		_valorCampo = "";
	}

	if (nodo.Attribute(ATR_CAMPO_AUX)) {
        _campoAux = nodo.Attribute(ATR_CAMPO_AUX);
	}
	else {
		_campoAux = "";
	}

	this->completarAtributos();
}

