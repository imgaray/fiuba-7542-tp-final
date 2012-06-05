/*
 * M_Fechas.cpp
 *
 *  Created on: 01/06/2012
 *      Author: migue
 */

#include "M_Fechas.h"
#include "Utilitario.h"
#include <iostream>

#define MUL_ANIO 	10000
#define MUl_MES 	100
#define MUL_DIA		1

#define F_MES 'M'
#define F_BIMES 'B'
#define F_TRIMES 'T'
#define F_CUAT 'C'
#define F_SEMES 'S'
#define F_RANGO 'R'


Fecha M_Fechas::fecha(int dia, int mes, int anio) {
	Fecha fecha;
	FechaNumerica nfecha = 0;
	std::stringstream sstream;
	if (anio > 0 && mes > 0 && mes <= 12 && dia > 0 && dia <= 31) {
		nfecha = anio * MUL_ANIO + mes * MUl_MES + dia * MUL_DIA;
		sstream << nfecha;
		sstream >> fecha;
	}
	return fecha;
}

FechaNumerica M_Fechas::convertir(const Fecha& fecha) {
	std::stringstream sstream;
	sstream << fecha;

	FechaNumerica nfecha;
	sstream >> nfecha;
	return nfecha;
}

Fecha M_Fechas::convertir(const FechaNumerica& fecha, int ancho) {
	std::stringstream sstream;
    sstream.width(ancho);
    sstream.fill('0');
	sstream << fecha;
	Fecha nfecha;
	sstream >> nfecha;
	return nfecha;
}


Fecha M_Fechas::convertir(const FechaNumerica& fecha) {
	std::stringstream sstream;
	sstream << fecha;
	Fecha nfecha;
	sstream >> nfecha;
	return nfecha;
}
bool M_Fechas::esRango(const Fecha& fecha) {
	bool res;
	switch (fecha[0]) {
	case F_MES:
	case F_BIMES:
	case F_TRIMES:
	case F_CUAT:
	case F_SEMES:
	case F_RANGO:
		res = true; break;
	default: res = false; break;
	}

	return res;
}

bool M_Fechas::esSimple(const Fecha& fecha) {
	return !esRango(fecha);
}

Fecha M_Fechas::rango(const Fecha &f1, const Fecha& f2) {
	if (esRango(f1) || esRango(f2))
		return "";

	Fecha fecha;
	fecha.clear();
	fecha += F_RANGO;
	fecha += sep_fecha;
	if (convertir(f1) < convertir(f2)) {
		fecha += f1;
		fecha += sep_fecha;
		fecha += f2;
	}
	else {
		fecha += f2;
		fecha += sep_fecha;
		fecha += f1;
	}
	return fecha;
}

void M_Fechas::desarmar(const Fecha& rango, Fecha& f1 ,Fecha& f2) {
	if (esRango(rango) == false)
		return;

	Fecha nf1,nf2;

	switch (rango[0]) {
		case F_MES: desarmarMes(rango, f1, f2);
			break;
		case F_BIMES:desarmarBimes(rango, f1, f2);
			break;
		case F_TRIMES:desarmarTrimes(rango, f1, f2);
			break;
		case F_CUAT: desarmarCuatrimes(rango, f1, f2);
			break;
		case F_SEMES: desarmarSemes(rango, f1, f2);
			break;
		case F_RANGO:
					nf1 = Utilitario::separar(rango, sep_fecha, 1);
					nf2 = Utilitario::separar(rango, sep_fecha, 2);
					f1 = nf1; f2 = nf2;
				break;
		default: break;
	}
}

void M_Fechas::armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha) {
	fecha += sep_fecha;
	fecha += M_Fechas::convertir(x, 2);
	// std::cout << "NUMERO : " << x <<" STRING: \"" <<M_Fechas::convertir(x, 2)  << "\""<< std::endl;
	fecha += sep_fecha;
	fecha += anio;

}

Fecha M_Fechas::mes(int mes, const std::string& anio) {
	if (mes > 0 && mes <= 12) {
		Fecha fecha;
		fecha = F_MES;
		armarFecha(mes, anio, fecha);
		return fecha;
	}
	else {
		return "";
	}
}

Fecha M_Fechas::bimestre(int bim, const std::string& anio) {
	if (bim > 0 && bim <= 6) {
		Fecha fecha;
		fecha = F_BIMES;
		armarFecha(bim, anio,fecha);
		return fecha;
	}
	else {
		return "";
	}
}

Fecha M_Fechas::trimestre(int tri, const std::string& anio) {
	if (tri > 0 && tri <= 4) {
		Fecha fecha;
		fecha = F_TRIMES;
		armarFecha(tri, anio, fecha);
		return fecha;
	}
	else {
		return "";
	}
}

Fecha M_Fechas::cuatrimestre(int cuat, const std::string& anio) {
	if (cuat > 0 && cuat <= 3) {
		Fecha fecha;
		fecha = F_CUAT;
		armarFecha(cuat, anio, fecha);
		return fecha;
	}
	else {
		return "";
	}
}

Fecha M_Fechas::semestre(int sem, const std::string& anio) {
	if (sem > 0 && sem <= 2) {
		Fecha fecha;
		fecha = F_SEMES;
		armarFecha(sem, anio, fecha);
		return fecha;
	}
	else {
		return "";
	}
}

void M_Fechas::desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul){
	FechaNumerica coef = M_Fechas::convertir(Utilitario::separar(rango, sep_fecha, 1));
	FechaNumerica anio = M_Fechas::convertir(Utilitario::separar(rango, sep_fecha, 2));

	anio = anio * MUL_ANIO;

	if (mul == 1) {
		coef++;
	}

	if (coef == 1) {
		f1 = M_Fechas::convertir(anio + coef * MUl_MES + 1 * MUL_DIA);
	}
	else {
		f1 = M_Fechas::convertir(anio + (coef-1) *mul* MUl_MES + 1 * MUL_DIA);
	}

	if (coef * mul >= 12) {
		f2 = M_Fechas::convertir(anio + 1 * MUL_ANIO +  1* MUl_MES + 1 * MUL_DIA);
	}
	else {
		f2 = M_Fechas::convertir(anio + (coef)* mul * MUl_MES + 1 * MUL_DIA);
	}
}

void M_Fechas::desarmarMes(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 1);
}

void M_Fechas::desarmarBimes(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 2);
}

void M_Fechas::desarmarTrimes(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 3);
}

void M_Fechas::desarmarCuatrimes(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 4);
}

void M_Fechas::desarmarSemes(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 6);
}
