#include "FiltradorConfigModelo.h"
#include "Organizacion.h"
#include "FiltradorHelper.h"


#define NOMBRE_NODO "Filtrador_Config_Modelo"
#define ATR_CAMPO "atr_campo"
#define ATR_VALOR_CAMPO "atr_valor_campo"
#define ATR_CAMPO_AUX "atr_campo_aux"



FiltradorConfigModelo::FiltradorConfigModelo(unsigned _ID)
: comboDimension(NULL), comboFecha(NULL), comboHecho(NULL),
  entryExtra(NULL),
  botonEliminar(NULL),
  ID(_ID) {

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

void FiltradorConfigModelo::setComboDimension(Gtk::ComboBoxText* comboDim) {
    comboDimension = comboDim;
    comboDimension->clear_items();
    for (unsigned i = 0; i < Organizacion::cantidadCampos(); ++i)
        comboDimension->append_text(Organizacion::nombreCampo(i));

    comboDimension->signal_changed().connect(sigc::mem_fun(*this,
        &FiltradorConfigModelo::on_combo_dimension_changed));
}

void FiltradorConfigModelo::setComboFecha(Gtk::ComboBoxText* _comboFecha) {
    comboFecha = _comboFecha;

    FiltradorHelper::getInstancia().popularComboFecha(comboFecha);

    comboFecha->set_active(0);
}

void FiltradorConfigModelo::setComboHecho(Gtk::ComboBoxText* _comboHecho) {
    comboHecho = _comboHecho;

    FiltradorHelper::getInstancia().popularComboHechoInput(comboHecho);

    comboHecho->set_active(0);
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

void FiltradorConfigModelo::on_boton_eliminar_clicked() {
    _signal_delete_filtrador.emit(ID);
}

NodoXml FiltradorConfigModelo::serializar() {
	NodoXml nodo(NOMBRE_NODO);

	nodo.SetAttribute(ATR_CAMPO, campoSelecc.c_str());
	nodo.SetAttribute(ATR_VALOR_CAMPO, _valorCampo.c_str());
	nodo.SetAttribute(ATR_CAMPO_AUX, _campoAux.c_str());

	// @todo sacar el cout
	std::cout << "FiltradorConfigModelo Serializado++++++++" << std::endl;

	return nodo;
}

void FiltradorConfigModelo::deserializar(const NodoXml& nodo) {

	if (nodo.Attribute(ATR_CAMPO)) {
		campoSelecc = nodo.Attribute(ATR_CAMPO);
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

	// @todo sacar el cout
	std::cout << "FiltradorConfigModelo Deserializado******" << std::endl;
}

