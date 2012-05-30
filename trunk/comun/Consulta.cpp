/*
 * Consulta.cpp
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#include "Consulta.h"

Consulta::Consulta() : _filtros(), _campos(_filtros) {
	_consultaValida = true;
	_consultaDeCliente = true;
}

Consulta::Consulta(const Consulta& original) {
	this->_campos = original._campos;
	this->_consultaDeCliente = original._consultaDeCliente;
	this->_consultaValida = original._consultaValida;
	this->_entradas = original._entradas;
	this->_resultados = original._resultados;
	this->_filtros = original._filtros;
}

Consulta::~Consulta() {
}

std::string Consulta::serializar() {
	std::string datos;

	if (_consultaValida) {
		if (_consultaDeCliente)
			datos = mensaje_cliente;
		else
			datos = mensaje_agente;
	}
	else {
		return;
	}

	datos += sep_tipo;

	cargarFiltros(datos);

	cargarEntradas(datos);

	cargarResultados(datos);

	datos += sep_fin;

	return datos;
}


void Consulta::deserializar(const std::string& consulta) {
	_consultaValida = true;
	if (consulta[0] == mensaje_agente) {
		this->_consultaDeCliente = false;
	}
	else if (consulta[0] == mensaje_cliente) {
		this->_consultaDeCliente = true;
	}
	else {
		_consultaValida = false;
		return;
	}

	size_t primer_sep = consulta.find(sep_tipo, 0);
	size_t segundo_sep = consulta.find(sep_tipo, primer_sep + 1);
	size_t tercer_sep = consulta.find(sep_tipo, segundo_sep + 1);
	size_t ultimo_sep = consulta.find(sep_tipo, tercer_sep + 1);

	std::string filtros = &consulta.c_str()[primer_sep];
	filtros.resize(segundo_sep - primer_sep);

	guardarFiltros(filtros);

	std::string entradas = &consulta.c_str()[segundo_sep];
	entradas.resize(tercer_sep - segundo_sep);

	guardarEntradas(entradas);

	std::string resultados = &consulta.c_str()[tercer_sep];
	resultados.resize(ultimo_sep - tercer_sep);

	guardarResultados(resultados);
}

void Consulta::guardarFiltros(const std::string& filtros) {
	size_t pos_sep_filtro = 0;
	size_t pos_sep_ant;
	size_t pos_sep_valor;
	std::string n_filtro;
	std::string valor;

	bool hayMasFiltros = true;
	while (hayMasFiltros) {
		n_filtro = &filtros.c_str()[pos_sep_filtro];
		pos_sep_ant = pos_sep_filtro;
		pos_sep_filtro = filtros.find(sep_datos, pos_sep_filtro + 1);
		n_filtro.resize(pos_sep_filtro - pos_sep_ant - 1);

		pos_sep_valor = filtros.find(sep_valor, pos_sep_filtro);
		valor = &filtros[pos_sep_valor];
		valor.resize(pos_sep_filtro - pos_sep_valor - 1);

		_filtros[n_filtro] = valor;

		hayMasFiltros = (filtros.find(sep_datos, pos_sep_filtro + 1) != std::string::npos);
	}
}


void Consulta::guardarResultados(const std::string& resultados){
	size_t pos_sep = 0;
	size_t pos_sep_ant;
	std::string resultado;

	bool hayMasResultados = true;

	while (hayMasResultados) {
		resultado = &resultados[pos_sep];
		pos_sep_ant = pos_sep;
		pos_sep = resultados.find(sep_datos, pos_sep + 1);

		resultado.resize(pos_sep - pos_sep_ant - 1);

		_resultados.push_back(resultado);

		hayMasResultados = (resultados.find(sep_datos, pos_sep + 1) != std::string::npos);
	}
}

void Consulta::agregarFiltro(const std::string filtro,
			const std::string valor) {
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

void Consulta::agregarResultado(const std::string resultado) {
	if (resultado.empty() == false) {
		this->_resultados.push_back(resultado);
	}
}

const std::string& Consulta::filtro(int indice) {
	if (_filtros.size() > indice && indice >= 0) {
		Filtros::iterator it = _filtros.begin();
		it += indice;

		return it->first;
	}
	else
		return "";
}

const std::string& Consulta::valorFiltro(int indice) {
	if (_filtros.size() > indice && indice >= 0) {
		Filtros::iterator it = _filtros.begin();
		it += indice;

		return it->second;
	}
	else
		return "";
}

const std::string& Consulta::valorFiltro(const string& filtro) {
	Filtros::iterator it = this->_filtros.find(filtro);

	if (it != _filtros.end()) {
		return it->second;
	}
	else {
		return "";
	}
}

const std::string& Consulta::entrada(int indice) {
	if (_entradas.size() > indice && indice >= 0) {
		Entradas::iterator it = _entradas.begin();
		it += indice;

		return it->first;
	}
	else {
		return "";
	}
}

const std::string& Consulta::valorEntrada(int indice) {
	if (_entradas.size() > indice && indice >= 0) {
		Entradas::iterator it = _entradas.begin();
		it += indice;

		return it->second;
	}
	else {
		return "";
	}
}

const std::string& Consulta::valorEntrada(const std::string& entrada) {
	Entradas::iterator it = _entradas.find(entrada);
	if (it != _entradas.end()) {
		return it->second;
	}
	else {
		return "";
	}
}

const std::string& Consulta::resultado(int indice) {
	if (_resultados.size() > indice && indice >= 0) {
		return _resultados[indice];
	}
	else {
		return "";
	}
}

void Consulta::definirComoConsultaAgente() {
	this->_consultaDeCliente = false;
}

void Consulta::definirComoConsultaCliente() {
	this->_consultaDeCliente = true;
}

int Consulta::cantidadResultados() const {
	return _resultados.size();
}

int Consulta::cantidadFiltros() const {
	return _filtros.size();
}

int Consulta::cantidadEntradas() const {
	return _entradas.size();
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
