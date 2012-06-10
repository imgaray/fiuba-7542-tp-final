/*
 * ComparadorHechos.cpp
 *
 *  Created on: 09/06/2012
 *      Author: migue
 */

#include "ComparadorHechos.h"
#include "../../comun/Consulta.h"
#include "../../comun/Utilitario.h"
#include "../../comun/Organizacion.h"
#include "TiposDeDatos.h"

ComparadorHechos::ComparadorHechos(bool filtarHechos, const Consulta& c) {
	unsigned cantHechos = 0;
	_filtrarHechos = filtarHechos;

	if (_filtrarHechos) {
		for (unsigned i = 0; i < c.cantidadFiltros() ; i++) {
			if (Organizacion::esHecho(c.filtro(i))) {
				cantHechos++;
				_indHechos.push_back(Organizacion::indiceDeCampo(c.filtro(i)));
				_valorHechos.push_back(c.valorFiltro(c.filtro(i)));
			}
		}

		for (unsigned i = 0; i < c.cantidadEntradas() ; i++) {
			if (Organizacion::esHecho(c.entrada(i))) {
				cantHechos++;
				_indHechos.push_back(Organizacion::indiceDeCampo(c.entrada(i)));
				_valorHechos.push_back(c.valorEntrada(c.entrada(i)));
			}
		}
	}
}

ComparadorHechos::~ComparadorHechos() {
}


bool ComparadorHechos::registroAceptado(const std::string& reg) {
	if (!_filtrarHechos)
		return true;

	bool aceptado = true;

	for (unsigned i=0; i < _indHechos.size() && aceptado; i++) {
		_campoActual = Utilitario::separar(reg, sep_campos, _indHechos[i]);
		aceptado = aceptado && aceptarHecho(_valorHechos[i], _campoActual);
	}

	return aceptado;
}
bool ComparadorHechos::aceptarHecho(const std::string& hechoComp, const std::string& vHecho) {
	if (hechoComp.size() < 2)
		return false;

	char comparador = hechoComp[0];
	unsigned hCompNum = Utilitario::convertirAEntero(&hechoComp.c_str()[1]);

	unsigned hecho = Utilitario::convertirAEntero(vHecho);
	bool aceptado = false;

	switch (comparador) {
	case '>':
		aceptado = (hecho > hCompNum);
		break;
	case '<':
		aceptado = (hecho < hCompNum);
		break;
	case '=':
		aceptado = (hecho == hCompNum);
		break;
	default: break;
	}

	return aceptado;
}
