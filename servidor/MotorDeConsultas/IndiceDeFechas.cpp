/*
 * IndiceDeFechas.cpp
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#include "IndiceDeFechas.h"
#include "../../comun/M_Fechas.h"

IndiceDeFechas::IndiceDeFechas() {
	// TODO Auto-generated constructor stub

}

IndiceDeFechas::~IndiceDeFechas() {
	// TODO Auto-generated destructor stub
}

void IndiceDeFechas::recuperar(const Fecha& fecha, Lista_Id& ids) {
	ids.clear();

	if (M_Fechas::esRango(fecha)) {
		Fecha f1, f2;
		M_Fechas::desarmar(fecha, f1, f2);

		FechaNumerica nf1, nf2;
		nf1 = M_Fechas::convertir(f1);
		nf2 = M_Fechas::convertir(f2);

		this->guardarDesdeRango(nf1, nf2, ids);
	}
	else {
		FechaNumerica nFecha = M_Fechas::convertir(fecha);

		this->guardarIDs(nFecha, ids);

	}

	ids.sort();
	ids.unique();
}


void IndiceDeFechas::guardarFecha(const Fecha& fecha,const Id_Registro& id) {
	if (M_Fechas::esSimple(fecha)) {
		FechaNumerica nfecha = M_Fechas::convertir(fecha);
		std::pair < FechaNumerica, Id_Registro> par(nfecha, id);
		this->_fechas.insert(par);
	}
}

const Lista_Id& IndiceDeFechas::recuperar(const Fecha & fecha) {
	this->_res.clear();

	if (M_Fechas::esRango(fecha)) {
		Fecha f1, f2;
		M_Fechas::desarmar(fecha, f1, f2);

		FechaNumerica nf1, nf2;
		nf1 = M_Fechas::convertir(f1);
		nf2 = M_Fechas::convertir(f2);

		this->guardarDesdeRango(nf1, nf2);
	}
	else {
		FechaNumerica nFecha = M_Fechas::convertir(fecha);

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
	std::pair < MapaDeFechas::iterator , MapaDeFechas::iterator > ret;
	MapaDeFechas::iterator it;
	ret = _fechas.equal_range(fecha);

	for (it = ret.first ; it != ret.second ; ++it) {
		_res.push_back(it->second);
	}
}

void IndiceDeFechas::guardarIDs(const FechaNumerica& fecha, Lista_Id& ids) {
	std::pair < MapaDeFechas::iterator , MapaDeFechas::iterator > ret;
	MapaDeFechas::iterator it;
	ret = _fechas.equal_range(fecha);

	for (it = ret.first ; it != ret.second ; ++it) {
		ids.push_back(it->second);
	}
}

void IndiceDeFechas::guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2) {
	MapaDeFechas::iterator itf1 = _fechas.lower_bound(f1);
	MapaDeFechas::iterator itf2 = _fechas.lower_bound(f2);

	MapaDeFechas::iterator it;

	for (it = itf1 ; it != itf2 ; it++) {
		_res.push_back(it->second);
	}
}

void IndiceDeFechas::guardarDesdeRango(const FechaNumerica& f1, const FechaNumerica& f2, Lista_Id& ids) {
	MapaDeFechas::iterator itf1 = _fechas.lower_bound(f1);
	MapaDeFechas::iterator itf2 = _fechas.lower_bound(f2);

	MapaDeFechas::iterator it;

	for (it = itf1 ; it != itf2 ; it++) {
		ids.push_back(it->second);
	}
}
