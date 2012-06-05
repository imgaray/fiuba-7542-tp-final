/*
 * BaseDeDatos.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "BaseDeDatos.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include "../../comun/Organizacion.h"
#include "../../comun/Utilitario.h"

BaseDeDatos::BaseDeDatos(const std::string rutaArchivo) :
	_archDatos(rutaArchivo) {

	_indDimensiones = new Indice<Dimension> [Organizacion::cantidadDimensionesSimples()];
	_cnjDimensiones = new ConjuntoValoresDimension [Organizacion::cantidadDimensionesSimples()];
	// _indHechos = Indice<Hecho> [Organizacion::cantidadHechos()];
}

BaseDeDatos::~BaseDeDatos() {
	delete[] _indDimensiones;
	delete[] _cnjDimensiones;
	//delete[] _indHechos;
}

Respuesta BaseDeDatos::resolverConsulta(const Consulta& consulta) {
	Respuesta resp;
	if (consulta.esConsultaDeTablaPivote()) {
		resolverTablaPivote(consulta, resp);
	}
	else if (consulta.agregacion()) {
		this->resolverSinAgregacion(consulta, resp);
	}
	else {
		this->resolverSinAgregacion(consulta, resp);
	}

	return resp;
}


void BaseDeDatos::calcularInterseccion(const Lista_Id& l1, const Lista_Id& l2, Lista_Id& destino) {
	Lista_Id::const_iterator it1 = l1.begin();
	Lista_Id::const_iterator it2 = l2.begin();

	// destino.clear();

	while (it1 != l1.end() && it2 != l2.end()) {
		if (*it1 > *it2) {
			++it2;
		}
		else if (*it1 < *it2) {
			++it1;
		}
		else {
			destino.push_back(*it1);
			++it1;
			++it2;
		}
	}
}

void BaseDeDatos::resolverSinAgregacion(const Consulta& consulta, Respuesta& resp) {
	if (consulta.cantidadEntradas() == 0 && consulta.cantidadFiltros() == 0) {
		bool dimEnResultado = false;
		Dimension dim;

		for (unsigned i = 0 ; i < consulta.cantidadResultados() && !dimEnResultado ; i ++) {
			dimEnResultado = (Organizacion::esDimension(consulta.resultado(i))
							&& !Organizacion::esDimensionEspecial(consulta.resultado((unsigned)i)));
			if (dimEnResultado)
				dim = consulta.resultado((unsigned)i);
		}


		if (dimEnResultado) {
			int indice = Organizacion::indiceDeCampo(dim);
			ConjuntoValoresDimension::iterator it = _cnjDimensiones[indice].begin();
			ConjuntoValoresDimension::iterator it_end = _cnjDimensiones[indice].end();

			for ( ; it != it_end ; it++) {
				resp.agregar(*it);
				resp.filaCompletada();
			}
		}
		else {

			/*
			 * Agregar todos lo hechos a la tabla
			 * Verificar que sea consulta Valida... creo que no
			 */
		}
	}
	else {
		// ....
		// Filtrar y obtener los registros
	}
}

void BaseDeDatos::resolverConAgregacion(const Consulta& consulta, Respuesta& resp) {

}

void BaseDeDatos::resolverTablaPivote(const Consulta& consulta, Respuesta& resp){

}


void BaseDeDatos::obtenerIDs(const std::string& dimension,
							const std::string& valorDim,
							Lista_Id& lista) {
	int indice = Organizacion::indiceDeCampo(dimension);
	_indDimensiones[indice].recuperar(valorDim, lista);
}


void BaseDeDatos::calcularFiltros(const Consulta& consulta, Lista_Id& lista) {
	if (consulta.cantidadFiltros() > 0) {
		lista.clear();
		Lista_Id listaAux1, listaAux2;
		std::string filtro = consulta.filtro(0);
		std::string valor = consulta.valorFiltro(0);

		int indice = Organizacion::indiceDeCampo(filtro);

		_indDimensiones[indice].recuperar(valor, listaAux1);

		for (unsigned i = 1 ; i < consulta.cantidadFiltros() ; i++) {
			filtro = consulta.filtro(i);
			valor = consulta.valorFiltro(filtro);
			indice = Organizacion::indiceDeCampo(filtro);

			_indDimensiones[indice].recuperar(valor, listaAux2);

			calcularInterseccion(listaAux1, listaAux2, lista);
			listaAux1 = lista;
		}
	}
}

void BaseDeDatos::calcularEntradas(const Consulta& consulta, Lista_Id& lista) {
	if (consulta.cantidadEntradas() > 0) {
		lista.clear();
		Lista_Id listaAux1, listaAux2;
		std::string entrada = consulta.entrada(0);
		std::string valor = consulta.valorEntrada(0);

		int indice = Organizacion::indiceDeCampo(entrada);

		_indDimensiones[indice].recuperar(valor, listaAux1);

		for (unsigned i = 1 ; i < consulta.cantidadEntradas() ; i++) {
			entrada = consulta.entrada(i);
			valor = consulta.valorEntrada(entrada);
			indice = Organizacion::indiceDeCampo(entrada);

			_indDimensiones[indice].recuperar(valor, listaAux2);

			calcularInterseccion(listaAux1, listaAux2, lista);
			listaAux1 = lista;
		}
	}
}

Respuesta BaseDeDatos::agregarEntrada(const Consulta& entrada) {
	Respuesta resp;

	std::string reg;

	unsigned i = 0 ;
	while (i < entrada.cantidadCampos()) {
		reg += entrada.campo(i);

		i++;
		if (i < entrada.cantidadCampos()){
			reg += sep_datos;
			actualizacion += sep_datos;
		}
	}

	Id_Registro id = _archDatos.guardarRegistro(reg);

	actualizarIndices(reg, id);


	/*
	 * Tratar la respuesta
	 * ...
	 * ...
	 */

	return resp;
}

void BaseDeDatos::actualizarIndices(const std::string& entrada, const Id_Registro& id) {
	std::string campoCompleto;
	std::string campo;
	std::string valor;

	bool seguirProcesando = true;
	int ind = 0;

	for (unsigned i = 0 ; i < Organizacion::cantidadCampos() ; i++) {
		campoCompleto = Utilitario::separar(entrada, sep_datos, ind);

		if (campoCompleto.empty() == false) {
			campo = Utilitario::separar(campoCompleto, sep_valor, i);

			if (Organizacion::esDimensionEspecial(Organizacion::indiceDeCampo(i))) {
				_indFechas.guardarFecha(valor, id);
			}
			else if (Organizacion::esDimension(Organizacion::indiceDeCampo(i))) {
				_indDimensiones[Organizacion::indiceDeCampo(campo)].agregar(valor, id);
			}

			/*
			 *Asegurar si hay que guardar los hechos...
			 */

	}
}
