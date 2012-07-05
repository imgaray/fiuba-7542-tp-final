#include "InputConfigModelo.h"

#define NOMBRE_NODO "InputConfigModelo"

InputConfigModelo::InputConfigModelo(unsigned _ID)
: FiltradorSoloDimensionConfigModelo(_ID) {}

InputConfigModelo::~InputConfigModelo() {}


NodoXml InputConfigModelo::serializar() {
	NodoXml nodo(NOMBRE_NODO);
	nodo.SetAttribute(ATR_CAMPO, this->campoSelecc.c_str());

	return nodo;
}

void InputConfigModelo::deserializar(const NodoXml& nodo) {
	if (nodo.Attribute(ATR_CAMPO) != NULL) {
		this->campoSelecc = nodo.Attribute(ATR_CAMPO);
	}
	else {
		// @todo lanzar Excepcion
	}
}
