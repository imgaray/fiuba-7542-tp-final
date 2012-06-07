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

	//resolucion que envia todos los registros....
	__guardarRegistros(consulta, resp);
	return resp;


	if (consulta.esConsultaDeTablaPivote()) {
		resolverTablaPivote(consulta, resp);
	}
//	else if (consulta.agregacion()) {
//		this->resolverSinAgregacion(consulta, resp);
//	}
//	else {
//		this->resolverSinAgregacion(consulta, resp);
//	}

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
		if (i < entrada.cantidadCampos())
			reg += sep_campos;
	}

	Id_Registro id = _archDatos.guardarRegistro(reg);

	actualizarIndices(reg, id);


	/*
	 * Tratar la respuesta
	 * ...
	 */

	return resp;
}

void BaseDeDatos::actualizarIndices(const std::string& entrada, const Id_Registro& id) {
	std::string dimension;

	int indd = 0;

	for (unsigned i = 0 ; i < Organizacion::cantidadDimensionesTotal() ; i++) {
		dimension = Utilitario::separar(entrada, sep_datos, i);

		if (dimension.empty() == false) {

			if (Organizacion::esDimensionEspecial(Organizacion::nombreDimension(i))) {
				_indFechas.guardarFecha(dimension, id);
			}
			else {
				_indDimensiones[Organizacion::indiceDeCampoSimple(Organizacion::nombreCampoSimple(indd))].agregar(dimension, id);
				indd++;

			}
		}
	}
}

void BaseDeDatos::resolverConsultaNormal(const Consulta& consulta, Respuesta& respuesta) {
	Lista_Id listaReg;
	bool huboFiltrado = filtrarDatos(consulta,listaReg);
	bool hayDimEnResultados = hayResultadosDeDimensiones(consulta);
	bool filtrarHechos = hayFiltrosDeHechos(consulta);

	MapaCombinaciones mCombin;

	if (huboFiltrado) {
		if (hayDimEnResultados) {
			guardarCombinaciones(consulta, listaReg, mCombin, filtrarHechos);
			hacerAgregaciones(consulta, mCombin, respuesta);
		}
		else {
			// Con filtros
			// sin dimensiones en resultado
		}
	}
	else {
		if (hayDimEnResultados) {
			guardarCombinaciones(consulta, mCombin, filtrarHechos);
			hacerAgregaciones(consulta,mCombin,respuesta);
		}
		else {
			// Sin ningun filtro
			// sin dimensiones en resultados
		}
	}
}

void BaseDeDatos::guardarCombinaciones(const Consulta& consulta, Lista_Id& lReg, MapaCombinaciones& mComb, bool filtrarHechos) {
	std::string reg;
	Lista_Id::iterator it;
	for (it = lReg.begin(); it != lReg.end() ; ++it) {
		reg = this->_archDatos.obtenerRegistro(*it);
		std::string combinacion;
		for (unsigned i = 0; i < consulta.cantidadResultados() ; i++ ) {
			if (Organizacion::esDimension(consulta.resultado(i))) {
				combinacion +=Utilitario::separar(reg, sep_campos,Organizacion::indiceDeCampo(consulta.resultado(i)));
				combinacion +=sep_campos;
			}
		}
		mComb.insert(parDeConjunto(combinacion, *it));
	}
}

void BaseDeDatos::guardarCombinaciones(const Consulta& consulta, MapaCombinaciones& mComb, bool filtrarHechos) {
	std::string reg;
	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = this->_archDatos.obtenerRegistro(id);
		std::string combinacion;
		for (unsigned i = 0; i < consulta.cantidadResultados() ; i++ ) {
			if (Organizacion::esDimension(consulta.resultado(i))) {
				combinacion +=Utilitario::separar(reg, sep_campos,Organizacion::indiceDeCampo(consulta.resultado(i)));
				combinacion +=sep_campos;
			}
		}
		mComb.insert(parDeConjunto(combinacion, id));
	}
}

bool BaseDeDatos::hayFiltrosDeHechos(const Consulta& consulta) {
	for (unsigned i = 0 ; i < consulta.cantidadFiltros() ; i++) {
		if (Organizacion::esHecho(consulta.filtro(i)))
			return true;
	}
	return false;
}

bool BaseDeDatos::hayResultadosDeDimensiones(const Consulta& consulta) {
	for (unsigned i = 0 ; i < consulta.cantidadResultados() ; i++) {
		if (Organizacion::esDimension((consulta.resultado(i))))
			return true;
	}
	return false;
}

bool BaseDeDatos::filtrarDatos(const Consulta& consulta, Lista_Id& listaReg) {
	if (consulta.cantidadEntradas() == 0 && consulta.cantidadFiltros() == 0)
		return false;

	Lista_Id idFiltros, idEntradas;

	if (consulta.cantidadEntradas() > 0)
		calcularEntradas(consulta, idEntradas);


	if (consulta.cantidadFiltros() > 0)
		calcularFiltros(consulta, idFiltros);

	calcularInterseccion(idEntradas, idFiltros, listaReg);

	return true;
}

void BaseDeDatos::hacerAgregaciones(const Consulta& consulta, const MapaCombinaciones& mComb, Respuesta& resp) {
    MapaCombinaciones::const_iterator it, itActual;
    itActual = mComb.begin(); 
    Lista_Id ids_aAgregar;
    
    for (it = mComb.begin(); it != mComb.end(); ++it) {
        if (itActual->first == it->first) {
            ids_aAgregar.push_back(it->second);
        }
        else {
            itActual = it;     
            // hacer una agregacion individual para la lista
        }
    }
}

void BaseDeDatos::agregaParaFila(const Consulta& cons, 
        const Combinacion& combinacion, 
        const Lista_Id& ids, 
        Respuesta& resp) {
    
    std::string nomCampoRes;
    unsigned cantDim = 0;
    unsigned cantHechos = 0;
    
    for (unsigned i = 0; i < cons.cantidadResultados() ;i++) {
        nomCampoRes = cons.resultado(i);
        if (Organizacion::esDimension(nomCampoRes))
            cantDim++;
        else if (Organizacion::esHecho(nomCampoRes))
            cantHechos++;
    }
    
    std::vector<std::string> resolucionesDim;
    std::vector<unsigned> indDim;
    if (cantDim > 0) {
    	resolucionesDim.reserve(cantDim);
    	indDim.reserve(cantDim);
    }

    std::vector<std::string> resolucionesHec;
    std::vector<unsigned> indHechos;
    if (cantHechos > 0) {
    	resolucionesHec.reserve(cantHechos);
    	indHechos.reserve(cantHechos);
    }

    for (unsigned i = 0; i < cons.cantidadResultados() ; i ++) {
    	if (Organizacion::esDimension(cons.resultado(i))) {
    		indDim.push_back(i);
    	}
    	else if (Organizacion::esHecho(cons.resultado(i))) {
    		indHechos.push_back(i);
    	}
    }

    std::string campo;

    unsigned ind = 0;
    for (unsigned i = 0 ; i < indDim.size() ; i++, ind++) {
    	campo = Utilitario::separar(combinacion, sep_campos, ind);
    	resolucionesDim.push_back(campo);
    }

    /*
     * Resolver la agregacion para un campo y guardarla en
     * resolucioneHec.
     * ...
     * ...
     * ...
     * ...
     */
    Lista_Id::const_iterator itIds;
    std::string reg;
    for (itIds = ids.begin() ; itIds != ids.end() ; ++itIds) {
    	reg = _archDatos.obtenerRegistro(*itIds);

    	for (unsigned i = 0; i < indHechos.size() ; i++) {
    		// resolver la agregacion de cada registro en cada indice
    	}
    }


    //... Fin de agregacion de los registros

    std::vector <unsigned>::const_iterator itd,ith;
    itd = indDim.begin();
    ith = indHechos.begin();

    std::vector<std::string>::const_iterator itrd,itrh;
    itrd = resolucionesDim.begin();
    itrh = resolucionesHec.begin();


    //agrego los campo en el orden correcta a la consulta
    while (itd != indDim.end() || ith != indHechos.end()) {

    	if (*itd > *ith) {
    		// agrego el campo de resolucion a la respuesta
    		resp.agregar(*itrh);

    		++itrh;
    		++ith;
    	}else if (*itd < *ith) {
    		// agregado el campo de resolucion a la respuesta
    		resp.agregar(*itrd);

    		++itrd;
    		++itd;
    	}
    }


    //Indico a la respuesta que se completo una fila
    resp.filaCompletada();
}


void BaseDeDatos::__guardarRegistros(const Consulta& cons, Respuesta& resp) {
	resp.limpiar();
	resp.definirColumnas(cons.cantidadResultados());

	std::string reg;
	std::string campoAAgregar;
	unsigned indCampo;
	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = _archDatos.obtenerRegistro(id);
		for (unsigned i = 0; i < cons.cantidadResultados() ; i++) {
			indCampo = Organizacion::indiceDeCampo(cons.resultado(i));
			campoAAgregar = Utilitario::separar(reg,sep_campos, indCampo);
			resp.agregar(campoAAgregar);
		}

		resp.filaCompletada();
	}
}
