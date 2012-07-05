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
#include "ComparadorHechos.h"
#include "../../comun/ErrorOrganizacion.h"

BaseDeDatos::BaseDeDatos(const std::string rutaArchivo) :
	_archDatos(rutaArchivo) {
	_cantDimensionesSimples =Organizacion::cantidadDimensionesSimples();

	if (_cantDimensionesSimples == 0)
		throw ErrorOrganizacion();

	_indDimensiones = new Indice<Dimension> [_cantDimensionesSimples];

	cargarIndices();
}

void BaseDeDatos::cargarIndices() {
	std::string reg;
	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = _archDatos.obtenerRegistro(id);
		actualizarIndices(reg, id);
	}
}

BaseDeDatos::~BaseDeDatos() {
	delete[] _indDimensiones;
	//delete[] _cnjDimensiones;
	//delete[] _indHechos;
}

Respuesta BaseDeDatos::resolverConsulta(const Consulta& consulta) {
	Respuesta resp;
	//_mutex.lock();

	if (consulta.esConsultaDeTablaPivote()) {
		resolverTablaPivote(consulta, resp);
	}
	else if (consulta.esConsultaDeCliente()) {
		resolverConsultaNormal(consulta,resp);
	}

	//_mutex.unlock();
	return resp;
}


void BaseDeDatos::calcularInterseccion(const Lista_Id& l1, const Lista_Id& l2, Lista_Id& destino) const {
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

void BaseDeDatos::resolverTablaPivote(const Consulta& consulta, Respuesta& resp) {
	Lista_Id listaReg;
	bool huboFiltrado = filtrarDatos(consulta,listaReg);
/*  comentada esta variable porque no se usa
	bool hayDimEnResultados = hayResultadosDeDimensiones(consulta);
*/
	bool filtrarHechos = hayFiltrosDeHechos(consulta);


	resp.limpiar();
	Consulta cX(consulta), cY(consulta);

	cX.limpiarResultados();
	cY.limpiarResultados();

	for (unsigned i = 0; i < consulta.cantVarXTabla() ; i++) {
		cX.agregarResultado(consulta.xDeTablaPivote(i));
	}

	for (unsigned i = 0; i < consulta.cantVarYTabla() ; i++) {
		cY.agregarResultado(consulta.yDeTablaPivote(i));
	}

	MapaCombinaciones mCombX, mCombY;

	if (huboFiltrado) {
		guardarCombinacionesTP(cX, mCombX, filtrarHechos, &listaReg);
		guardarCombinacionesTP(cY, mCombY, filtrarHechos, &listaReg);
	}
	else {
		guardarCombinacionesTP(cX, mCombX, filtrarHechos);
		guardarCombinacionesTP(cY, mCombY, filtrarHechos);
	}

	hacerAgregacionesTP(cX, mCombX, cY, mCombY, consulta, resp);


}

void BaseDeDatos::hacerAgregacionesTP(const Consulta& cX,
		const MapaCombinaciones& mCombX,
		const Consulta& cY,
		const MapaCombinaciones& mCombY,
		const Consulta& cons,
		Respuesta& resp) {
	Utilitario u;
	Lista_Id interseccionXY , lauxX, lauxY;

	parItMapaCombinaciones rango;
	MapaCombinaciones::const_iterator itCombX, itCombY, itAuxX, itAuxY;
	/*
	 * Guarda los primeros espacios en blanco para el grupo Y, y guardo tambien las primeras
	 * filas que contendran los datos del grupo X
	 */
	for (unsigned i = 0; i < cX.cantidadResultados() ; i++) {

		for (unsigned j = 0; j < cY.cantidadResultados() ; j++) {
			resp.agregar("...");
		}

		itCombX = mCombX.begin();
		while (itCombX != mCombX.end()) {
			rango = mCombX.equal_range(itCombX->first);
			resp.agregar(u.separar(itCombX->first, sep_campos, i));
			itCombX = rango.second;
		}

		resp.filaCompletada();
	}



	/*
	 * Doble ciclo que itera y calcula los resultados para cada fila en cada campo
	 */
	itCombY = mCombY.begin();
	while (itCombY != mCombY.end()) {
		rango = mCombY.equal_range(itCombY->first);

		lauxY.clear();

		/*
		 * Guardo la combinacion para una combinacion del grupo Y
		 */
		for (itAuxY = rango.first; itAuxY != rango.second ; ++itAuxY) {
			lauxY.push_back(itAuxY->second);
		}

		// Agrego los campos de Y de para cada Fila nueva
		for (unsigned i = 0; i < cY.cantidadResultados() ; i++) {
			resp.agregar(u.separar(itCombY->first, sep_campos, i));
		}


		/////////////////////////////////////////////////
		/*
		 * Guarda la lista de ids para una combinacion del grupo X
		 */

		itCombX = mCombX.begin();
		while (itCombX != mCombX.end()) {
			rango = mCombX.equal_range(itCombX->first);

			lauxX.clear();

			for (itAuxX = rango.first; itAuxX != rango.second ; ++itAuxX) {
				lauxX.push_back(itAuxX->second);
			}

			itCombX = rango.second;


			//Calcular las agregaciones para una campo de respuesta
			interseccionXY.clear();
			calcularInterseccion(lauxX, lauxY, interseccionXY);

			// se calcula la agregacion
			std::string resAgregacion;

			calcularAgregacionTP(interseccionXY, cons, resAgregacion);

			resp.agregar(resAgregacion);

		}

		resp.filaCompletada();

		itCombY = mCombY.equal_range(itCombY->first).second;
	}
}


void BaseDeDatos::calcularAgregacionTP(const Lista_Id& ids, const Consulta& cons, std::string& campoRes) {
	Lista_Id::const_iterator it;
	std::string reg, hecho;
	unsigned hechoNumerico = 0 , acum = 0, auxProm = 0;
	unsigned indHecho = Organizacion::indiceDeCampo(cons.resultado(0));
	Agregacion agre = cons.agregacionDeResultado(0);
	Utilitario u;


	for (it = ids.begin(); it != ids.end(); ++it) {
		reg = _archDatos.obtenerRegistro(*it);

		hecho = u.separar(reg, sep_campos, indHecho);
		hechoNumerico = u.convertirAEntero(hecho);

		if (agre == PROM) {
			calcularPromedio(acum, auxProm, hechoNumerico);
		}
		else {
			calcularAgregacion(agre, acum, hechoNumerico);
		}
	}

	campoRes = u.convertirAString(acum);
}



void BaseDeDatos::guardarCombinacionesTP(const Consulta& consulta,
		MapaCombinaciones& mComb,
		bool filtrarHechos,
		Lista_Id* lReg) {

	Utilitario u;
	bool iterarPorLista = (lReg != NULL);

	std::string reg;
	Lista_Id::iterator it;
	Id_Registro id = 0 ,idActual;
	ComparadorHechos compHechos(filtrarHechos, consulta);

	bool condClico;

	// Estable y evaluo la condicion inicial

	if (iterarPorLista) {
		it = lReg->begin();
		condClico = (it != lReg->end());
	}
	else {
		condClico = (id < _archDatos.cantidadRegistros());
	}

//	for (it = lReg.begin(); it != lReg.end() ; ++it)
	while (condClico)
	{
		if (iterarPorLista)
			idActual = *it;
		else
			idActual = id;

		reg = this->_archDatos.obtenerRegistro(idActual);
		std::string combinacion;
		unsigned numArgRegistro;

		if (compHechos.registroAceptado(reg)) {

			for (unsigned i = 0; i < consulta.cantidadResultados() ; i++ ) {
					numArgRegistro = Organizacion::indiceDeCampo(consulta.resultado(i));
					combinacion +=u.separar(reg, sep_campos, numArgRegistro);
					combinacion +=sep_campos;
			}
			mComb.insert(parDeConjunto(combinacion, idActual));
		}

		if (iterarPorLista) {
			++it;
			condClico = (it != lReg->end());
		}
		else {
			id++;
			condClico = (id < _archDatos.cantidadRegistros());
		}
	}
}


void BaseDeDatos::calcularFiltros(const Consulta& consulta, Lista_Id& lista) const {
	bool hayDimension = false;
	unsigned cantFiltrosSimples = 0;
	for (unsigned j = 0 ; j < consulta.cantidadFiltros() && !hayDimension; j++){
		lista.clear();
		Lista_Id listaAux1, listaAux2;
		std::string filtro = consulta.filtro(j);
		std::string valor = consulta.valorFiltro(j);

		int indice;

		if (Organizacion::esDimensionEspecial(filtro)) {
			_indFechas.recuperar(valor, listaAux1);
			hayDimension = true;
			cantFiltrosSimples++;
		}
		else if (Organizacion::esDimension(filtro)) {
			indice = Organizacion::indiceDeCampoSimple(filtro);
			_indDimensiones[indice].recuperar(valor, listaAux1);
			hayDimension = true;
			cantFiltrosSimples++;
		}

		for (unsigned i = (j + 1) ; i < consulta.cantidadFiltros() && hayDimension ; i++) {
			if (Organizacion::esDimension(consulta.filtro(i))) {
				filtro = consulta.filtro(i);
				valor = consulta.valorFiltro(filtro);

				if (Organizacion::esDimensionEspecial(filtro)) {
					_indFechas.recuperar(valor, listaAux2);
					cantFiltrosSimples++;
				}
				else {
					indice = Organizacion::indiceDeCampoSimple(filtro);
					_indDimensiones[indice].recuperar(valor, listaAux2);
					cantFiltrosSimples++;
				}

				calcularInterseccion(listaAux1, listaAux2, lista);
				listaAux1 = lista;
			}
		}

		if (cantFiltrosSimples == 1)
				lista = listaAux1;
	}
}

void BaseDeDatos::calcularEntradas(const Consulta& consulta, Lista_Id& lista) const {
	bool hayDimension = false;
	unsigned cantEntradasSimples = 0;
	for (unsigned j = 0 ; j < consulta.cantidadEntradas() && !hayDimension; j++){
		lista.clear();
		Lista_Id listaAux1, listaAux2;
		std::string entrada = consulta.entrada(j);
		std::string valor = consulta.valorEntrada(j);
		int indice;

		if (Organizacion::esDimensionEspecial(entrada)) {
			_indFechas.recuperar(valor, listaAux1);
			hayDimension = true;
			cantEntradasSimples++;
		}
		else if (Organizacion::esDimension(entrada)) {
			indice = Organizacion::indiceDeCampoSimple(entrada);
			_indDimensiones[indice].recuperar(valor, listaAux1);
			hayDimension = true;
			cantEntradasSimples++;
		}

		for (unsigned i = (j + 1) ; i < consulta.cantidadEntradas() && hayDimension ; i++) {
			entrada = consulta.entrada(i);
			if (Organizacion::esDimension(entrada)) {
				valor = consulta.valorEntrada(entrada);

				if (Organizacion::esDimensionEspecial(entrada)) {
					_indFechas.recuperar(valor, listaAux2);
					cantEntradasSimples++;
				}
				else {
					indice = Organizacion::indiceDeCampoSimple(entrada);
					_indDimensiones[indice].recuperar(valor, listaAux2);
					cantEntradasSimples++;
				}

				calcularInterseccion(listaAux1, listaAux2, lista);
				listaAux1 = lista;
			}
		}
		if (cantEntradasSimples == 1)
		lista = listaAux1;
	}
}

Respuesta BaseDeDatos::agregarEntrada(const Consulta& entrada) {
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

	Respuesta resp("OK");

	return resp;
}

void BaseDeDatos::actualizarIndices(const std::string& entrada, const Id_Registro& id) {
	Utilitario u;
	std::string dimension;
	std::string nomDimension;
	// indice de dimension de la clase Organizacion
	int indd = 0;
	int indice;

	for (unsigned i = 0 ; i < Organizacion::cantidadDimensionesTotal() ; i++) {
		dimension = u.separar(entrada, sep_datos, i);
		nomDimension = Organizacion::nombreDimension(i);


		if (dimension.empty() == false) {
			if (Organizacion::esDimensionEspecial(nomDimension)) {
				_indFechas.guardarFecha(dimension, id);
			}
			else {
				indice = Organizacion::indiceDeCampoSimple(nomDimension);
				_indDimensiones[indice].agregar(dimension, id);
				indd++;
			}
		}
	}
}

void BaseDeDatos::resolverConsultaNormal(const Consulta& consulta, Respuesta& respuesta) {
	respuesta.definirColumnas(consulta.cantidadResultados());
	Lista_Id listaReg;
	bool huboFiltrado = filtrarDatos(consulta,listaReg);
	bool hayDimEnResultados = hayResultadosDeDimensiones(consulta);
	bool filtrarHechos = hayFiltrosDeHechos(consulta);
	MapaCombinaciones mCombin;

	if (huboFiltrado) {

		if (listaReg.size() == 0) {
			respuesta.mensajeInterno(Respuesta::respuestaVacia);
  		}
		else if (hayDimEnResultados) {
			guardarCombinaciones(consulta, listaReg, mCombin, filtrarHechos);
			hacerAgregaciones(consulta, mCombin, respuesta);
		}
		else {
			// Con filtros
			// sin dimensiones en resultado
			guardarHechos(consulta, listaReg, respuesta);
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
			guardarHechos(consulta, respuesta);
		}
	}

	if (respuesta.cantidadFilas() == 0) {
		respuesta.mensajeInterno(Respuesta::respuestaVacia);
  }
	else {
		respuesta.mensajeInterno(Respuesta::respuestaValida);
	}


}

bool BaseDeDatos::aplicarAgregacionHechos(const Consulta& cons, std::vector <unsigned>& indice) const {
	bool hacerAgregacion = true;
	for (unsigned i = 0; i < cons.cantidadResultados() && hacerAgregacion; i++) {
		hacerAgregacion = hacerAgregacion && (cons.agregacionDeResultado(i) != NADA);
		indice.push_back(Organizacion::indiceDeCampo(cons.resultado(i)));
	}

	return hacerAgregacion;
}

void BaseDeDatos::guardarHechos(const Consulta& cons, Respuesta& resp) {
	Utilitario u;
	resp.definirColumnas(cons.cantidadResultados());

	std::vector <unsigned> _indHechos;
	bool hacerAgre = aplicarAgregacionHechos(cons, _indHechos);
	std::string reg, campo;
	unsigned campoNumerico;
	unsigned auxProm = 0;
	std::vector <unsigned> _acumHechos(_indHechos.size(), 0);

	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = _archDatos.obtenerRegistro(id);

		for (unsigned i = 0; i < cons.cantidadResultados() ; i++) {
			campo = u.separar(reg, sep_campos, _indHechos[i]);
			if (hacerAgre) {
				campoNumerico = u.convertirAEntero(campo);
				if (cons.agregacionDeResultado(i) == PROM) {
					calcularPromedio(_acumHechos[i], auxProm, campoNumerico);
				}
				else {
					calcularAgregacion(cons.agregacionDeResultado(i), _acumHechos[i], campoNumerico);
				}
			}
			else {
				resp.agregar(campo);
			}
		}

		if (!hacerAgre) {
			resp.filaCompletada();
		}

	}

	if (hacerAgre) {
		for (unsigned i = 0; i < _acumHechos.size() ; i++) {
			campo = u.convertirAString(_acumHechos[i]);
			resp.agregar(campo);
		}
		resp.filaCompletada();
	}
}


void BaseDeDatos::guardarHechos(const Consulta& cons,const Lista_Id& ids, Respuesta& resp) {
	Utilitario u;
	resp.definirColumnas(cons.cantidadResultados());

	std::vector <unsigned> _indHechos;
	bool hacerAgre = aplicarAgregacionHechos(cons, _indHechos);
	std::string reg, campo;
	unsigned campoNumerico;
	unsigned auxProm = 0;
	std::vector <unsigned> _acumHechos(_indHechos.size(), 0);


	Lista_Id::const_iterator it;

	for (it = ids.begin() ; it != ids.end() ; ++it) {
		reg = _archDatos.obtenerRegistro(*it);

		for (unsigned i = 0; i < cons.cantidadResultados() ; i++) {
			campo = u.separar(reg, sep_campos, _indHechos[i]);
			if (hacerAgre) {
				campoNumerico = u.convertirAEntero(campo);
				if (cons.agregacionDeResultado(i) == PROM) {
					calcularPromedio(_acumHechos[i], auxProm, campoNumerico);
				}
				else {
					calcularAgregacion(cons.agregacionDeResultado(i), _acumHechos[i], campoNumerico);
				}
			}
			else {
				resp.agregar(campo);
			}
		}

		if (!hacerAgre) {
			resp.filaCompletada();
		}

	}

	if (hacerAgre) {
		for (unsigned i = 0; i < _acumHechos.size() ; i++) {
			campo = u.convertirAString(_acumHechos[i]);
			resp.agregar(campo);
		}
		resp.filaCompletada();
	}
}

void BaseDeDatos::guardarCombinaciones(const Consulta& consulta, Lista_Id& lReg, MapaCombinaciones& mComb, bool filtrarHechos) {
	Utilitario u;
	std::string reg;
	Lista_Id::iterator it;

	ComparadorHechos compHechos(filtrarHechos, consulta);

	/*
	 * Completar para que filtre registros con filtro de "HECHOS"...
	 *
	 * Hecho++
	 */

	for (it = lReg.begin(); it != lReg.end() ; ++it) {
		reg = this->_archDatos.obtenerRegistro(*it);
		std::string combinacion;
		unsigned numArgRegistro;

		if (compHechos.registroAceptado(reg)) {

			for (unsigned i = 0; i < consulta.cantidadResultados() ; i++ ) {
				if (Organizacion::esDimension(consulta.resultado(i))) {
					numArgRegistro = Organizacion::indiceDeCampo(consulta.resultado(i));
					combinacion +=u.separar(reg, sep_campos, numArgRegistro);
					combinacion +=sep_campos;
				}
			}
			mComb.insert(parDeConjunto(combinacion, *it));
		}
	}
}

void BaseDeDatos::guardarCombinaciones(const Consulta& consulta, MapaCombinaciones& mComb, bool filtrarHechos) {
	Utilitario u;
	std::string reg;
	std::string combinacion;
	ComparadorHechos compHechos(filtrarHechos, consulta);

	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = this->_archDatos.obtenerRegistro(id);
		combinacion.clear();
		if (compHechos.registroAceptado(reg))
		{
			for (unsigned i = 0; i < consulta.cantidadResultados() ; i++ ) {
				if (Organizacion::esDimension(consulta.resultado(i))) {
					combinacion +=u.separar(reg, sep_campos,Organizacion::indiceDeCampo(consulta.resultado(i)));
					combinacion +=sep_campos;
				}
			}
			mComb.insert(parDeConjunto(combinacion, id));
		}
	}
}

bool BaseDeDatos::hayFiltrosDeHechos(const Consulta& consulta) const {
	for (unsigned i = 0 ; i < consulta.cantidadFiltros() ; i++) {
		if (Organizacion::esHecho(consulta.filtro(i)))
			return true;
	}

	for (unsigned i = 0 ; i < consulta.cantidadEntradas() ; i++) {
		if (Organizacion::esHecho(consulta.entrada(i)))
			return true;
	}
	return false;
}

bool BaseDeDatos::hayResultadosDeDimensiones(const Consulta& consulta) const {
	for (unsigned i = 0 ; i < consulta.cantidadResultados() ; i++) {
		if (Organizacion::esDimension((consulta.resultado(i))))
			return true;
	}
	return false;
}

bool BaseDeDatos::filtrarDatos(const Consulta& consulta, Lista_Id& listaReg) const {
	unsigned cantFiltrosS = 0;
	for (unsigned i=0 ; i < consulta.cantidadFiltros() ; i++) {
		if (Organizacion::esDimension(consulta.filtro(i)))
			cantFiltrosS++;
	}

	unsigned cantEntradasS = 0;
	for (unsigned i=0 ; i < consulta.cantidadEntradas() ; i++) {
		if (Organizacion::esDimension(consulta.entrada(i)))
			cantEntradasS++;
	}

	bool hayFiltros = (cantFiltrosS > 0);
	bool hayEntradas = (cantEntradasS > 0);


	if (hayFiltros == false && hayEntradas == false)
		return false;

	Lista_Id idFiltros, idEntradas;

	if (hayEntradas)
		calcularEntradas(consulta, idEntradas);


	if (hayFiltros)
		calcularFiltros(consulta, idFiltros);

	if (hayFiltros && hayEntradas)
		calcularInterseccion(idEntradas, idFiltros, listaReg);
	else if (hayFiltros)
		listaReg = idFiltros;
	else
		listaReg = idEntradas;

	return true;
}

void BaseDeDatos::hacerAgregaciones(const Consulta& consulta, const MapaCombinaciones& mComb, Respuesta& resp) {
    MapaCombinaciones::const_iterator it, itActual, itAux;
    itActual = mComb.begin();
    Lista_Id ids_aAgregar;
    bool ultimoHecho = false;

    for (it = mComb.begin(); it != mComb.end(); ++it) {
        if (itActual->first == it->first) {
            ids_aAgregar.push_back(it->second);
            ultimoHecho = false;
        }
        else {

            // hacer una agregacion individual para la lista
        	//_mutex.lock();
            agregaParaFila(consulta, itActual->first, ids_aAgregar, resp);
            //_mutex.unlock();
            ids_aAgregar.clear();
            itActual = it;
            --it;
            ultimoHecho = true;
        }
    }

    if (mComb.size() > 0 && ultimoHecho == false) {
    	//_mutex.lock();
    	 agregaParaFila(consulta, itActual->first, ids_aAgregar, resp);
    	//_mutex.unlock();
    }
}

void BaseDeDatos::agregaParaFila(const Consulta& cons,
        const Combinacion& combinacion,
        const Lista_Id& ids,
        Respuesta& resp) {
	Utilitario u;

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

    // En donde se van a guardar las resoluciones para las dimensiones
    std::vector<std::string> resolucionesDim;
    // Guarda las posiciones de las dimensiones para el orden de resultados de la Consulta
    std::vector<unsigned> indDim;
    if (cantDim > 0) {
    	resolucionesDim.reserve(cantDim);
    	indDim.reserve(cantDim);
    }

	// En donde se van a guardar las resoluciones para los hechos
    std::vector<std::string> resolucionesHec;
    // Guarda las posiciones de los hechos para el orden de resultados de la Consulta
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
    	campo = u.separar(combinacion, sep_campos, ind);
    	resolucionesDim.push_back(campo);
    }

    /*
     * Resolver la agregacion para un campo y guardarla en
     * resolucioneHec.
     */

    std::vector <unsigned> resHechos(cantHechos, 0);
    unsigned auxPromedio = 0;


    Lista_Id::const_iterator itIds;
    std::string reg;

    for (itIds = ids.begin() ; itIds != ids.end() ; ++itIds) {
    	reg = _archDatos.obtenerRegistro(*itIds);

        for (unsigned i = 0; i < cantHechos ; i++) {
        	// indice de hecho para obternerlo desde el regsitro
        	unsigned iHecho = Organizacion::indiceDeCampo(cons.resultado(indHechos[i]));
        	campo = u.separar(reg, sep_campos, iHecho);

        	unsigned campoNumerico = u.convertirAEntero(campo);
        	Agregacion agre = cons.agregacionDeResultado(indHechos[i]);

        	if ( agre == PROM) {
        		calcularPromedio(resHechos[i], auxPromedio, campoNumerico);
        	}
        	else {
        		calcularAgregacion(agre, resHechos[i], campoNumerico);
        	}
        }
    }

    for (unsigned i = 0; i < cantHechos ; i++) {
    	unsigned aux = resHechos[i];
    	//resolucionesHec[i] = u.convertirAString(aux);
    	resolucionesHec.push_back(u.convertirAString(aux));
    }


    //... Fin de agregacion de los registros

    /////////////////////////////////////
    /////////////////////////////////////

    std::vector <unsigned>::const_iterator itd,ith;
    itd = indDim.begin();
    ith = indHechos.begin();

    std::vector<std::string>::const_iterator itrd,itrh;
    itrd = resolucionesDim.begin();
    itrh = resolucionesHec.begin();

    if (cantHechos > 0 && cantDim > 0) {
		//agrego los campo en el orden correcta a la consulta
		while (itd != indDim.end() || ith != indHechos.end()) {
			if (itd == indDim.end() || (*itd > *ith)) {
				// agrego el campo de hecho de resolucion a la respuesta
				resp.agregar(*itrh);

				++itrh;
				++ith;
			}else if (ith == indHechos.end() || (*itd < *ith)) {
				// agregado el campo de dimension de resolucion a la respuesta
				resp.agregar(*itrd);

				++itrd;
				++itd;
			}
		}
    }
    else if (cantDim > 0) {
    	for (unsigned i = 0 ; i < cantDim ; i++) {
    		resp.agregar(*itrd);
    		++itrd;
    	}
    }
    else {
    	for (unsigned i = 0 ; i < cantHechos ; i++) {
			resp.agregar(*itrh);
			++itrh;
		}
    }
    //Indico a la respuesta que se completo una fila
    resp.filaCompletada();
}


void BaseDeDatos::calcularAgregacion(const Agregacion& agre, unsigned& acum, unsigned aAgregar) const {
	switch (agre) {
	case NADA:
		// Imprmir error;
		break;

	case MAX:
		if (aAgregar > acum)
			acum = aAgregar;
		break;

	case MIN:
		if (acum == 0)
			acum = aAgregar;
		if (aAgregar < acum)
			acum = aAgregar;
		break;

	case CONT:
		acum++;
		break;

	case SUM:
		acum += aAgregar;
		break;

	default: // imprimir error
		break;
	}
}

void BaseDeDatos::calcularPromedio(unsigned& acum, unsigned& cant, const unsigned& nuevoHecho) const {
	if (cant == 0) {
		cant = 1;
		acum = nuevoHecho;
	}
	else {
		acum = (acum*cant + nuevoHecho) / (cant + 1);
		cant++;
	}
}


void BaseDeDatos::borrarDatos() {
	_archDatos.borrarDatos();

	for (unsigned i = 0; i < Organizacion::cantidadDimensionesSimples() ; i++)
		_indDimensiones[i].limpiar();

	_indFechas.limpiar();
}

void BaseDeDatos::__guardarRegistros(const Consulta& cons, Respuesta& resp) {
	Utilitario u;
	resp.limpiar();
	resp.definirColumnas(cons.cantidadResultados());

	std::string reg;
	std::string campoAAgregar;
	unsigned indCampo;
	for (Id_Registro id = 0; id < _archDatos.cantidadRegistros() ; id++) {
		reg = _archDatos.obtenerRegistro(id);
		for (unsigned i = 0; i < cons.cantidadResultados() ; i++) {
			indCampo = Organizacion::indiceDeCampo(cons.resultado(i));
			campoAAgregar = u.separar(reg,sep_campos, indCampo);
			resp.agregar(campoAAgregar);
		}

		resp.filaCompletada();
	}
}

void BaseDeDatos::imprimirRegistro(Id_Registro id) {
	Utilitario u;

	if (id >= _archDatos.cantidadRegistros()) {
		std::cout << "REGISTRO NO EXISTE PARA ID: " << id << std::endl;
		return;
	}

	std::string reg = _archDatos.obtenerRegistro(id);

	for (unsigned i = 0; i < Organizacion::cantidadCampos() ; i++) {
		std::cout.width(15);
		std::cout << Organizacion::nombreCampo(i) << ": ";
		std::cout.width(15);
		std::cout << u.separar(reg,sep_campos,i);
		std::cout << "||";
	}
	std::cout << std::endl;
}
