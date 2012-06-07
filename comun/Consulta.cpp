/*
 * Consulta.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Consulta.h"
#include "Utilitario.h"

std::string Consulta::s_nulo = "";

#define TablaPivote 'T'

Consulta::Consulta() : _filtros(), _campos(_resultados) {
	_consultaValida = true;
	_consultaDeCliente = true;
	_consultaTablaPivote = false;
	_agregacion = NADA;
}

Consulta::Consulta(const Consulta& original) :
		_campos(_resultados) {
	// this->_campos = original._campos;
	this->_consultaDeCliente = original._consultaDeCliente;
	this->_consultaValida = original._consultaValida;
	this->_entradas = original._entradas;
	this->_resultados = original._resultados;
	this->_filtros = original._filtros;
}

Consulta::~Consulta() {
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

	cargarAgregacion(datos);

	if(_consultaTablaPivote)
		cargarVarDeTabla(datos);

	datos += sep_fin;

	return datos;
}

void Consulta::cargarAgregacion(std::string& datos) const {
	char agreg = (char)_agregacion;
	datos += agreg;
	datos += sep_tipo;
}

void Consulta::cargarVarDeTabla(std::string& datos) const {
	datos += _xTabla;
	datos += sep_datos;
	datos += _yTabla;

	datos += sep_tipo;
}

void Consulta::definirTablaPivote(const std::string& x, const std::string& y) {
	_xTabla = x;
	_yTabla = y;
	this->definirConsultaDeTablaPivote();
}

const std::string& Consulta::xDeTablaPivote() const {
	return _xTabla;
}
const std::string& Consulta::yDeTablaPivote() const {
	return _yTabla;
}

void Consulta::definirConsultaDeTablaPivote() {
	_consultaTablaPivote = true;
	_consultaDeCliente = true;
}

void Consulta::guardarVarDeTabla(const std::string& variables) {
	_xTabla = Utilitario::separar(variables, sep_datos, 0);
	_yTabla = Utilitario::separar(variables, sep_datos, 1);
}

void Consulta::guardarAgregacion(const std::string& agregacion) {
	_agregacion = (Agregacion)(agregacion[0]);
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
	Resultados::const_iterator it;
	for (it = _resultados.begin(); it != _resultados.end() ; ++it) {
		datos += *it;
		datos += sep_datos;
	}
	datos += sep_tipo;
}

void Consulta::deserializar(const std::string& consulta) {
	_consultaValida = true;

	std::string cabecera = Utilitario::separar(consulta, sep_tipo, 0);

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
		}
	}


	std::string filtros = Utilitario::separar(consulta, sep_tipo , 1);
	std::string entradas = Utilitario::separar(consulta, sep_tipo , 2);
	std::string resultados = Utilitario::separar(consulta, sep_tipo , 3);
	std::string agregacion = Utilitario::separar(consulta, sep_tipo, 4);

	guardarFiltros(filtros);

	guardarEntradas(entradas);

	guardarResultados(resultados);

	guardarAgregacion(agregacion);

	if (_consultaTablaPivote) {
		std::string variablesTabla = Utilitario::separar(consulta, sep_tipo, 5);
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
		filtroEntero = Utilitario::separar(filtros, sep_datos, ind);
		ind++;
		filtro = Utilitario::separar(filtroEntero, sep_valor, 0);
		valor = Utilitario::separar(filtroEntero, sep_valor, 1);

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
	std::string resultado;

	bool seguirGuardando = true;

	while (seguirGuardando) {
		resultado = Utilitario::separar(resultados, sep_datos, ind);
		ind++;
		if (resultado.empty() == false) {
			_resultados.push_back(resultado);
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
		entradaCompleta = Utilitario::separar(entradas, sep_datos, ind);
		ind++;

		entrada = Utilitario::separar(entradaCompleta, sep_valor, 0);
		valor = Utilitario::separar(entradaCompleta, sep_valor, 1);

		if (entrada.empty() == false && valor.empty() == false) {
			_entradas[entrada] = valor;
		}
		else {
			seguirGuardando = false;
		}
	}
}

Agregacion Consulta::agregacion() const {
	return _agregacion;
}

void Consulta::defininirAgregacion(Agregacion agregacion, const std::string& resultado) {
	this->_agregacion = agregacion;
	_resultados.push_front(resultado);
	_resultados.unique();
}

void Consulta::agregarFiltro(const std::string& filtro,
			const std::string& valor) {
	if (filtro.empty() == false && valor.empty() == false) {
		this->_filtros[filtro] = valor;
	}
}

void Consulta::agregarEntrada(const std::string& entrada,
				const std::string& valor) {
	if (entrada.empty() == false && valor.empty() == false) {
			this->_entradas[entrada] = valor;
		}
}

void Consulta::agregarResultado(const std::string& resultado) {
	if (resultado.empty() == false) {
		this->_resultados.push_back(resultado);
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
	_agregacion = NADA;
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

