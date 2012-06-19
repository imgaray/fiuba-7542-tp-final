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

#define F_SEMANA 	'X'
#define F_MES 		'M'
#define F_BIMES 	'B'
#define F_TRIMES 	'T'
#define F_CUAT 		'C'
#define F_SEMES 	'S'
#define F_ANIO 		'Z'
#define F_RANGO 	'R'

Fecha M_Fechas::fecha(const std::string& fechaComun) {
	Fecha fecha;

	if (!esFechaConvecional(fechaComun))
		return "";

	for (int i = 2 ; i >= 0 ; i--)
		fecha += u.separar(fechaComun, '-',i);

	return fecha;
}


bool M_Fechas::esFechaConvecional(const std::string& fecha) {
	bool resParcial;

	size_t pos;
	pos = fecha.find('-',0);
	if (pos != std::string::npos) {
		pos = fecha.find('-',pos + 1);
		if (pos != std::string::npos) {
			resParcial = true;
		}
		else{
			resParcial = false;
		}
	}
	else {
		resParcial = false;
	}

	bool resFinal = false;

	if (resParcial) {
		std::string dia = u.separar(fecha, '-', 0);
		int numDia = u.convertirAEntero(dia);

		if (numDia > 0 && numDia <= 31)
			resFinal = true;
		else
			resFinal = false;

		std::string mes = u.separar(fecha, '-', 1);
		int numMes = u.convertirAEntero(mes);

		if (numMes > 0 && numMes <= 12)
			resFinal = resFinal && true;
		else
			resFinal = false;

		std::string anio = u.separar(fecha, '-', 2);
		int numAnio = u.convertirAEntero(anio);

		if (numAnio > 1970)
			resFinal = resFinal && true;
		else
			resFinal = false;
	}


	return resFinal;
}

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
	case F_SEMANA:
	case F_MES:
	case F_BIMES:
	case F_TRIMES:
	case F_CUAT:
	case F_SEMES:
	case F_RANGO:
	case F_ANIO:
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
		return STR_NULA;

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
//	if (esRango(rango) == false)
//		return;

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
		case F_ANIO: desarmarAnio(rango, f1, f2);
			break;
		case F_RANGO:
					nf1 = u.separar(rango, sep_fecha, 1);
					nf2 = u.separar(rango, sep_fecha, 2);
					f1 = nf1; f2 = nf2;
				break;
		default:
					f1 = STR_NULA;
					f2 = STR_NULA;
				break;
	}
}

void M_Fechas::armarFecha(FechaNumerica x, const std::string& anio, Fecha& fecha) {
	fecha += sep_fecha;
	fecha += convertir(x, 2);
	// std::cout << "NUMERO : " << x <<" STRING: \"" <<M_Fechas::convertir(x, 2)  << "\""<< std::endl;
	fecha += sep_fecha;
	fecha += anio;

}

Fecha M_Fechas::anio(const std::string& anio) {
	if (u.convertirAEntero(anio) > 0) {
		Fecha fecha;
		fecha = F_ANIO;
		armarFecha(1,anio, fecha);
		return fecha;
	}
	else {
		return STR_NULA;
	}
}

Fecha M_Fechas::semana(int semana, const std::string& anio) {
	FechaNumerica nAnio = this->u.convertirAEntero(anio);
	bool esBisiesto = ((nAnio % 4) == 0);
	bool anioNuevo = false;

	if (semana > 53 || semana <= 0) {
		return STR_NULA;
	}

	int dia,mes;
	int diaInf, diaSup;

	diaInf = (semana - 1) * 7 + 1;

	if (semana <= 52){
		diaSup = semana * 7 + 1;
	}
	else {
		if (esBisiesto)
			diaSup = 366;
		else
			diaSup = 365;
		anioNuevo = true;

	}

//	std::cout << "Dia INf: " << diaInf << std::endl;
//	std::cout << "Dia Sup: " << diaSup << std::endl;

	calcularDia(diaInf, nAnio, dia, mes);
	Fecha fechaInf = fecha(dia, mes, nAnio);

	if (anioNuevo) {
		nAnio++;
		dia = 1;
		mes = 1;
	}
	else {
		calcularDia(diaSup, nAnio, dia, mes);
	}
	Fecha fechaSup = fecha(dia, mes, nAnio);


	Fecha fechaRes = rango(fechaInf, fechaSup);

	return fechaRes;
}


void M_Fechas::calcularDia(const int& diaAnio,
		const FechaNumerica& anio,
		int& dia,
		int& mes) {
	bool esBisiesto = ((anio % 4) == 0);
	bool calHecho = false;
	int sumMeses[12]={31,59,90,120,151,181,212,243,273,304,334,365};


	if (esBisiesto) {
		if (diaAnio <= (sumMeses[1] + 1)) {
			if (diaAnio <= sumMeses[0]) {
				mes = 1;
				dia = diaAnio;
			}
			else {
				mes = 2;
				dia = diaAnio - sumMeses[0];
			}
		}
		else {
			for (int i = 2; i < 12 && !calHecho ; i++) {
				if (diaAnio <= (sumMeses[i] + 1)) {
					mes = i + 1;
					dia = diaAnio - sumMeses[i - 1] - 1;
					calHecho = true;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 12 && !calHecho ; i++) {
			if (diaAnio <= sumMeses[i]) {
				mes = i + 1;
				if (i > 0) {
					dia = diaAnio - sumMeses[i - 1];
				}
				else {
					dia = diaAnio;
				}
				calHecho = true;
			}
		}
	}
}

Fecha M_Fechas::mes(int mes, const std::string& anio) {
	if (mes > 0 && mes <= 12) {
		Fecha fecha;
		fecha = F_MES;
		armarFecha(mes, anio, fecha);
		return fecha;
	}
	else {
		return STR_NULA;
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
		return STR_NULA;
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
		return STR_NULA;
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
		return STR_NULA;
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
		return STR_NULA;
	}
}

void M_Fechas::desarmarFechas(const Fecha& rango, Fecha& f1, Fecha& f2, unsigned mul){
	FechaNumerica coef = convertir(u.separar(rango, sep_fecha, 1));
	FechaNumerica anio = convertir(u.separar(rango, sep_fecha, 2));

	anio = anio * MUL_ANIO;


	f1 = convertir(anio + (1 + (coef -1) *(mul))*MUl_MES + 1*MUL_DIA);

	if ((coef*mul) == 12)
		f2 = convertir(anio + 1*MUL_ANIO + 1*MUl_MES + 1*MUL_DIA);
	else
		f2 = convertir(anio + (1 + coef *(mul))*MUl_MES + 1*MUL_DIA);
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

void M_Fechas::desarmarAnio(const Fecha& rango, Fecha& f1, Fecha& f2) {
	desarmarFechas(rango, f1, f2, 12);
}
