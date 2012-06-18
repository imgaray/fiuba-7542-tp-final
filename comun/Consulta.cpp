/*
 * Consulta.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Consulta.h"
#include "Utilitario.h"

std::string Consulta::s_nulo = STR_NULA;

#define TablaPivote 'T'

Consulta::Consulta() : _filtros(), _campos(_resultados) {
	_consultaValida = true;
	_consultaDeCliente = true;
	_consultaTablaPivote = false;

	_id = 0;
}

Consulta::Consulta(const Consulta& original) :
		_campos(_resultados) {
	// this->_campos = original._campos;
	this->_consultaTablaPivote = original._consultaTablaPivote;
	this->_consultaDeCliente = original._consultaDeCliente;
	this->_consultaValida = original._consultaValida;
	this->_entradas = original._entradas;
	this->_resultados = original._resultados;
	this->_agregaciones = original._agregaciones;
	this->_filtros = original._filtros;

	this->_id = original._id;
}

Consulta::~Consulta() {
}

Consulta& Consulta::operator=(const Consulta& original) {
	this->_consultaTablaPivote = original._consultaTablaPivote;
	this->_consultaDeCliente = original._consultaDeCliente;
	this->_consultaValida = original._consultaValida;
	this->_entradas = original._entradas;
	this->_resultados = original._resultados;
	this->_agregaciones = original._agregaciones;
	this->_filtros = original._filtros;

	this->_id = original._id;

	return *this;
}

void Consulta::definirID(const Id_Mensaje& id) {
	this->_id = id;
}

Id_Mensaje Consulta::devolverID() const {
	return this->_id;
}

std::string Consulta::serializar() const {
	std::string datos;

	if (_consultaValida) {
		if (_consultaDeCliente)
			datos = mensaje_cliente;
		else
			datos = mensaje_agente;
	}
	else {
		return datos;
	}

	if(_consultaTablaPivote) {
		datos += sep_datos;
		datos += TablaPivote;
	}

	datos += sep_tipo;

	cargarFiltros(datos);

	cargarEntradas(datos);

	cargarResultados(datos);

	cargarID(datos);

	//cargarAgregacion(datos);

	if(_consultaTablaPivote)
		cargarVarDeTabla(datos);

	datos += sep_fin;

	return datos;
}


void Consulta::cargarVarDeTabla(std::string& datos) const {
//	datos += _xTabla;
//	datos += sep_datos;
//	datos += _yTabla;
//
//	datos += sep_tipo;

	EntradasTabla::const_iterator it;

	for (it = _xTabla.begin() ; it != _xTabla.end() ;) {
		datos += *it;
		++it;
		if (it != _xTabla.end())
			datos += sep_valor;
	}

	datos +=  sep_datos;


	for (it = _yTabla.begin() ; it != _yTabla.end() ;) {
		datos += *it;
		++it;
		if (it != _xTabla.end())
			datos +=sep_valor;
	}

	datos += sep_tipo;
}

void Consulta::cargarID(std::string& datos) const {
	datos += u.convertirAString(this->_id);
	datos += sep_tipo;
}

void Consulta::guardarID(const std::string& id) {
	_id = u.convertirAEntero(id);
}

void Consulta::guardarVarDeTabla(const std::string& variables) {
	std::string x_Tabla = u.separar(variables, sep_datos, 0);
	std::string y_Tabla = u.separar(variables, sep_datos, 1);

	std::string campo = u.separar(x_Tabla, sep_valor, 0);
	unsigned ind = 0;
	while (campo.empty() == false) {
		ind++;
		_xTabla.push_back(campo);
		campo = u.separar(x_Tabla, sep_valor,ind);
	}

	campo = u.separar(y_Tabla, sep_valor, 0);
	ind = 0;
	while (campo.empty() == false) {
		ind++;
		_yTabla.push_back(campo);
		campo = u.separar(y_Tabla, sep_valor,ind);
	}
}

const std::string& Consulta::xDeTablaPivote(unsigned i) const {
	if (_xTabla.size() > i)
		return _xTabla[i];
	else
		return Consulta::s_nulo;
}
const std::string& Consulta::yDeTablaPivote(unsigned i) const {
	if (_yTabla.size() > i)
		return _yTabla[i];
	else
		return Consulta::s_nulo;
}

unsigned Consulta::cantVarXTabla() const {
	return _xTabla.size();
}
unsigned Consulta::cantVarYTabla() const {
	return _yTabla.size();
}

void Consulta::definirConsultaDeTablaPivote() {
	_consultaTablaPivote = true;
	_consultaDeCliente = true;
}


void Consulta::cargarFiltros(std::string& datos) const {
	Filtros::const_iterator it;
	for (it = _filtros.begin() ; it != _filtros.end() ; ++it) {
		datos += it->first;

		datos += sep_valor;

		datos += it->second;

		datos += sep_datos;
	}
	datos += sep_tipo;
}

void Consulta::cargarEntradas(std::string& datos) const{
	Entradas::const_iterator it;
	for (it = _entradas.begin(); it != _entradas.end() ; ++it) {
		datos += it->first;

		datos += sep_valor;

		datos += it->second;

		datos += sep_datos;
	}
	datos += sep_tipo;
}

void Consulta::cargarResultados(std::string& datos) const {
	Resultados::const_iterator itr;
	Agregaciones::const_iterator ita = _agregaciones.begin();
	for (itr = _resultados.begin(); itr != _resultados.end() ; ++itr, ++ita) {
		datos += *itr;
		if (_consultaDeCliente) {
			datos += sep_valor;
			datos += (char)*ita;
		}
		datos += sep_datos;
	}
	datos += sep_tipo;
}

void Consulta::deserializar(const std::string& consulta) {
	limpiar();
	_consultaValida = true;

	std::string cabecera = u.separar(consulta, sep_tipo, 0);

	if (cabecera[0] == mensaje_agente) {
		this->_consultaDeCliente = false;
	}
	else if (cabecera[0] == mensaje_cliente) {
		this->_consultaDeCliente = true;
	}
	else {
		_consultaValida = false;
		return;
	}

	if (cabecera.size() > 2) {
		if (cabecera[2] == TablaPivote) {
			_consultaTablaPivote = true;
			if (_consultaDeCliente == false)
				_consultaValida = false;
		}
	}


	std::string filtros = u.separar(consulta, sep_tipo , 1);
	std::string entradas = u.separar(consulta, sep_tipo , 2);
	std::string resultados = u.separar(consulta, sep_tipo , 3);
	std::string id = u.separar(consulta, sep_tipo, 4);

	guardarFiltros(filtros);

	guardarEntradas(entradas);

	guardarResultados(resultados);

	guardarID(id);

	// guardarAgregacion(agregacion);

	if (_consultaTablaPivote) {
		std::string variablesTabla = u.separar(consulta, sep_tipo, 5);
		guardarVarDeTabla(variablesTabla);
	}

}

void Consulta::guardarFiltros(const std::string& filtros) {
	size_t ind = 0;
	std::string filtroEntero;
	std::string filtro;
	std::string valor;

	bool hayMasFiltros = true;
	while (hayMasFiltros) {
		filtroEntero = u.separar(filtros, sep_datos, ind);
		ind++;
		filtro = u.separar(filtroEntero, sep_valor, 0);
		valor = u.separar(filtroEntero, sep_valor, 1);

		if (filtro.empty() == false && valor.empty() == false) {
			_filtros[filtro] = valor;
		}
		else {
			hayMasFiltros = false;
		}
	}
}


void Consulta::guardarResultados(const std::string& resultados){
	size_t ind = 0;
	std::string resCompleto, resNuevo, agregacion;

	bool seguirGuardando = true;

	while (seguirGuardando) {
		resCompleto = u.separar(resultados, sep_datos, ind);
		ind++;
		if (resCompleto.empty() == false) {

			if (_consultaDeCliente) {
				resNuevo = u.separar(resCompleto, sep_valor, 0);

				agregacion = u.separar(resCompleto, sep_valor, 1);
				_agregaciones.push_back((Agregacion)agregacion[0]);
			}
			else {
				resNuevo = resCompleto;
			}

			_resultados.push_back(resNuevo);
		}
		else {
			seguirGuardando = false;
		}
	}
}

void Consulta::guardarEntradas(const std::string& entradas) {
	size_t ind = 0;
	std::string entradaCompleta, entrada, valor;
	bool seguirGuardando = true;
	while (seguirGuardando){
		entradaCompleta = u.separar(entradas, sep_datos, ind);
		ind++;

		entrada = u.separar(entradaCompleta, sep_valor, 0);
		valor = u.separar(entradaCompleta, sep_valor, 1);

		if (entrada.empty() == false && valor.empty() == false) {
			_entradas[entrada] = valor;
		}
		else {
			seguirGuardando = false;
		}
	}
}

void Consulta::defininirAgregacion(Agregacion agregacion, const std::string& resultado) {
	/* VIEJO...
	this->_agregacion = agregacion;
	_resultados.push_front(resultado);
	_resultados.unique();
	*/
	_agregaciones.push_back(agregacion);
	_resultados.push_back(resultado);
}

void Consulta::agregarFiltro(const std::string& filtro,
			const std::string& valor) {
	if (filtro.empty() == false && valor.empty() == false) {
		this->_filtros[filtro] = valor;
	}
}

void Consulta::agregarEntrada(const std::string entrada,
				const std::string valor) {
	if (entrada.empty() == false && valor.empty() == false) {
			this->_entradas[entrada] = valor;
		}
}

void Consulta::agregarResultado(const std::string& resultado) {
	if (resultado.empty() == false) {
		this->_resultados.push_back(resultado);
		this->_agregaciones.push_back(NADA);
	}
}

void Consulta::agregarCampo(const std::string& campo) {
	this->agregarResultado(campo);
}

const std::string& Consulta::campo(unsigned indice) const{
	return this->resultado(indice);
}

const std::string& Consulta::filtro(unsigned indice) const{
	if (_filtros.size() > indice && indice >= 0) {
		Filtros::const_iterator it = _filtros.begin();
		for (unsigned i = 0; i < indice ; i++)
			++it;
		return it->first;
	}
	else
		return Consulta::s_nulo;
}

const std::string& Consulta::valorFiltro(unsigned indice) const {
	if (_filtros.size() > indice && indice >= 0) {
		Filtros::const_iterator it = _filtros.begin();
		for (unsigned i = 0; i < indice ; i++)
			++it;
		return it->second;
	}
	else
		return Consulta::s_nulo;
}

const std::string& Consulta::valorFiltro(const std::string& filtro) const {
	Filtros::const_iterator it = this->_filtros.find(filtro);

	if (it != _filtros.end()) {
		return it->second;
	}
	else {
		return Consulta::s_nulo;
	}
}

const std::string& Consulta::entrada(unsigned indice) const {
	if (_entradas.size() > indice) {
		Entradas::const_iterator it = _entradas.begin();
		for (unsigned i = 0; i < indice ;i++)
			++it;

		return it->first;
	}
	else {
		return Consulta::s_nulo;
	}
}

const std::string& Consulta::valorEntrada(unsigned indice) const {
	if (_entradas.size() > indice) {
		Entradas::const_iterator it;
		it = _entradas.begin();
		for (unsigned i = 0; i < indice ; i++)
			++it;

		return it->second;
	}
	else {
		return Consulta::s_nulo;
	}
}

const std::string& Consulta::valorEntrada(const std::string& entrada) const {
	Entradas::const_iterator it = _entradas.find(entrada);
	if (it != _entradas.end()) {
		return it->second;
	}
	else {
		return Consulta::s_nulo;
	}
}

const std::string& Consulta::resultado(unsigned indice) const {
	if (_resultados.size() > indice) {
		Resultados::const_iterator it;
		it = _resultados.begin();
		for (unsigned i = 0; i < indice ; i++)
			++it;
		return *it;
	}
	else {
		return Consulta::s_nulo;
	}
}

Agregacion Consulta::agregacionDeResultado(unsigned indice) const {
	if (_agregaciones.size() > indice) {
		return _agregaciones[indice];
	}
	else
		return NADA;
}

unsigned Consulta::cantidadResultados() const {
	return _resultados.size();
}

unsigned Consulta::cantidadFiltros() const {
	return _filtros.size();
}

unsigned Consulta::cantidadEntradas() const {
	return _entradas.size();
}

unsigned Consulta::cantidadCampos() const {
	return cantidadResultados();
}

void Consulta::definirComoConsultaAgente() {
	_consultaDeCliente = false;
}

void Consulta::definirComoConsultaCliente() {
	_consultaDeCliente = true;
}

bool Consulta::esConsultaDeCliente() const {
	return _consultaDeCliente;
}

bool Consulta::esConsultaDeAgente() const {
	return !_consultaDeCliente;
}

bool Consulta::esConsultaDeTablaPivote() const {
	return _consultaTablaPivote;
}

void Consulta::limpiar() {
	_agregaciones.clear();
	_campos.clear();
	_consultaDeCliente = true;
	_consultaTablaPivote = false;
	_consultaValida = true;
	_entradas.clear();
	_filtros.clear();
	_resultados.clear();
	_xTabla.clear();
	_yTabla.clear();
}

void Consulta::limpiarResultados() {
	_agregaciones.clear();
	_resultados.clear();
}

void Consulta::agregarXTablaP(const std::string& x) {
	_xTabla.push_back(x);
}

void Consulta::agregarYTablaP(const std::string& y) {
	_yTabla.push_back(y);
}
