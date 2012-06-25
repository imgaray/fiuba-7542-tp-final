/*
 * IndiceDeFechas.cpp
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#include "IndiceDeFechas.h"

IndiceDeFechas::IndiceDeFechas() {
	// TODO Auto-generated constructor stub

}

IndiceDeFechas::~IndiceDeFechas() {
	// TODO Auto-generated destructor stub
}

void IndiceDeFechas::recuperar(const Fecha& fecha, Lista_Id& ids) const{
	ids.clear();

	if (m_fechas.esRango(fecha)) {
		Fecha f1, f2;
		m_fechas.desarmar(fecha, f1, f2);

		FechaNumerica nf1, nf2;
		nf1 = m_fechas.convertir(f1);
		nf2 = m_fechas.convertir(f2);

		this->guardarDesdeRango(nf1, nf2, ids);
	}
	else if (m_fechas.esFechaConvecional(fecha)) {
		FechaNumerica nFecha = m_fechas.convertir(m_fechas.fecha(fecha));
		this->guardarIDs(nFecha, ids);
	}
	else {
		FechaNumerica nFecha = m_fechas.convertir(fecha);
		this->guardarIDs(nFecha, ids);
	}

	ids.sort();
	ids.unique();
}


void IndiceDeFechas::guardarFecha(const Fecha& fecha,const Id_Registro& id) {
	if (m_fechas.esSimple(fecha)) {
		FechaNumerica nfecha;
		if (m_fechas.esFechaConvecional(fecha)) {
			nfecha = m_fechas.convertir(m_fechas.fecha(fecha));
		}
		else {
			nfecha = m_fechas.convertir(fecha);
		}


		std::pair < FechaNumerica, Id_Registro> par(nfecha, id);
		this->_fechas.insert(par);
	}
}

const Lista_Id& IndiceDeFechas::recuperar(const Fecha & fecha) {
	this->_res.clear();

	if (m_fechas.esRango(fecha)) {
		Fecha f1, f2;
		m_fechas.desarmar(fecha, f1, f2);

		FechaNumerica nf1, nf2;
		nf1 = m_fechas.convertir(f1);
		nf2 = m_fechas.convertir(f2);

		this->guardarDesdeRango(nf1, nf2);
	}
	else {
		FechaNumerica nFecha = m_fechas.convertir(fecha);

		this->guardarIDs(nFecha);

	}

	_res.sort();
	_res.unique();


	return _res;
}

void IndiceDeFechas::limpiar() {
	_fechas.clear();
}

void IndiceDeFechas::guardarIDs(const FechaNumerica& fecha) {
	std::pair < MapaDeFechas::const_iterator , MapaDeFechas::const_iterator > ret;
	MapaDeFechas::const_iterator it;
	ret = _fechas.equal_range(fecha);

	for (it = ret.first ; it != ret.second ; ++it) {
		_res.push_back(it->second);
	}
}

void IndiceDeFechas::guardarIDs(const FechaNumerica& fecha, Lista_Id& ids) const{
	std::pair < MapaDeFechas::const_iterator , MapaDeFechas::const_iterator > ret;
	MapaDeFechas::const_iterator it;
	ret = _fechas.equal_range(fecha);

	for (it = ret.first ; it != ret.second ; ++it) {
		ids.push_back(it->second);
	}
}

void IndiceDeFechas::guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2) {
	MapaDeFechas::const_iterator itf1 = _fechas.lower_bound(f1);
	MapaDeFechas::const_iterator itf2 = _fechas.lower_bound(f2);

	MapaDeFechas::const_iterator it;

	for (it = itf1 ; it != itf2 ; it++) {
		_res.push_back(it->second);
	}
}

void IndiceDeFechas::guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2, Lista_Id& ids) const {
	MapaDeFechas::const_iterator itf1 = _fechas.lower_bound(f1);
	MapaDeFechas::const_iterator itf2 = _fechas.lower_bound(f2);

	MapaDeFechas::const_iterator it;

	for (it = itf1 ; it != itf2 ; it++) {
		ids.push_back(it->second);
	}
}
