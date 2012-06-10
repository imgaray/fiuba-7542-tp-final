#include "VerificadorConsultasH.h"
#include "../../comun/Consulta.h"
#include "../../comun/Organizacion.h"
#include "../../comun/Definiciones.h"

bool VerificadorConsultasH::verificarConsulta(const Consulta& consulta) {
	if (!consulta.esConsultaDeCliente())
		return false;

	return this->cClienteValida(consulta);
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

	if (!filtrosCorrectos(cons))
		return false;

	if (!entradasCorrectos(cons))
		return false;

	if (!_hayAgreEnHechos && _hayDimEnRes)
		return false;

	/*
	 * Agregar verificador de tabla pivote
	 * comprobando los campos
	 */


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

