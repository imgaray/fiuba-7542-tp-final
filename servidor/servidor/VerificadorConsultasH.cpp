#include "VerificadorConsultasH.h"
#include "../../comun/Consulta.h"
#include "../../comun/Organizacion.h"
#include "../../comun/Definiciones.h"
#include <iostream>

bool VerificadorConsultasH::verificarConsulta(const Consulta& consulta) {
  	if (!consulta.esConsultaDeCliente())
		return false;

	if (consulta.esConsultaDeTablaPivote())
		return this->cClienteTP(consulta);
	else
		return this->cClienteValida(consulta);//return true;
}

bool VerificadorConsultasH::hayDimesionesEnRes(const Consulta& cons) {
	for (unsigned i=0 ; i < cons.cantidadResultados(); i++) {
		if (Organizacion::esDimension(cons.resultado(i)))
			return true;
	}
	return false;
}
bool VerificadorConsultasH::hayHechosEnRes(const Consulta& cons) {
	for (unsigned i=0 ; i < cons.cantidadResultados(); i++) {
		if (Organizacion::esHecho(cons.resultado(i)))
			return true;
	}
	return false;
}

bool VerificadorConsultasH::hayAgregacionesEnHechos(const Consulta& cons) {
	bool hayAgre = false;

	for (unsigned i=0 ; i < cons.cantidadResultados() && !hayAgre ; i++) {
		if (Organizacion::esHecho(cons.resultado(i)))
			hayAgre = (cons.agregacionDeResultado(i) != NADA);
	}

	return hayAgre;
}

bool VerificadorConsultasH::cClienteValida(const Consulta& cons) {
	bool _hayAgreEnHechos = hayAgregacionesEnHechos(cons);
	bool _hayDimEnRes = hayDimesionesEnRes(cons);
	bool _hayHechosEnRes = hayHechosEnRes(cons);

	if (hayCamposNulos(cons)){
		return false;
	}

	if (!filtrosCorrectos(cons)) {
		return false;
	}

	if (!entradasCorrectos(cons)){
		return false;
	}

	if (!resultadoCorrectos(cons)){
		return false;
	}

	if ((_hayDimEnRes && _hayHechosEnRes) && !_hayAgreEnHechos){
		return false;
	}

	return true;
}

bool VerificadorConsultasH::filtrosCorrectos(const Consulta& cons) {
	for (unsigned i=0; i < cons.cantidadFiltros() ; i++) {
		if (!Organizacion::esDimension(cons.filtro(i)) &&
				!Organizacion::esHecho(cons.filtro(i)))
			return false;
	}
	return true;
}
bool VerificadorConsultasH::entradasCorrectos(const Consulta& cons) {
	for (unsigned i=0; i < cons.cantidadEntradas() ; i++) {
		if (!Organizacion::esDimension(cons.entrada(i)) &&
				!Organizacion::esHecho(cons.entrada(i)))
			return false;
	}
	return true;
}

bool VerificadorConsultasH::resultadoCorrectos(const Consulta& cons) {
	for (unsigned i = 0; i < cons.cantidadResultados() ; i++) {
		if (!Organizacion::esDimension(cons.resultado(i)) &&
				!Organizacion::esHecho(cons.resultado(i)))
			return false;
	}
	return true;
}

bool VerificadorConsultasH::cClienteTP(const Consulta& cons) {
	if (hayCamposNulos(cons))
		return false;

	if (!filtrosCorrectos(cons))
		return false;

	if (!entradasCorrectos(cons))
		return false;

	if (cons.cantVarXTabla() == 0 || cons.cantVarYTabla() == 0)
		return false;

	if (hayDimesionesEnRes(cons))
		return false;

	if (cons.cantidadResultados() > 1)
		return false;

	if (cons.agregacionDeResultado(0) == NADA)
		return false;

	if (!resultadoCorrectos(cons))
		return false;

	if (!camposTablaPivoteCorrectos(cons))
		return false;

	return true;
}

bool VerificadorConsultasH::camposTablaPivoteCorrectos(const Consulta& cons) {
	for (unsigned i = 0; i < cons.cantVarXTabla() ; i++) {
		if (!Organizacion::esDimension(cons.xDeTablaPivote(i)) &&
				!Organizacion::esHecho(cons.xDeTablaPivote(i)))
			return false;
	}

	for (unsigned i = 0; i < cons.cantVarYTabla() ; i++) {
		if (!Organizacion::esDimension(cons.yDeTablaPivote(i)) &&
				!Organizacion::esHecho(cons.yDeTablaPivote(i)))
			return false;
	}

	return true;
}


bool VerificadorConsultasH::hayCamposNulos(const Consulta& cons) {
	bool hayNulos = false;
	for (unsigned i = 0; i < cons.cantidadResultados() && !hayNulos; i++) {
		hayNulos = cons.resultado(i).empty();
	}

	for (unsigned i = 0; i < cons.cantidadFiltros() && !hayNulos; i++) {
		hayNulos = cons.filtro(i).empty() || cons.valorFiltro(i).empty();
	}

	for (unsigned i = 0; i < cons.cantidadEntradas() && !hayNulos; i++) {
		hayNulos = cons.entrada(i).empty() || cons.valorEntrada(i).empty();
	}


	if (cons.esConsultaDeTablaPivote()) {
		for (unsigned i = 0; i < cons.cantVarXTabla() && !hayNulos; i++) {
			hayNulos = cons.xDeTablaPivote(i).empty();
		}

		for (unsigned i = 0; i < cons.cantVarYTabla() && !hayNulos; i++) {
			hayNulos = cons.yDeTablaPivote(i).empty();
		}
	}

	return hayNulos;
}
