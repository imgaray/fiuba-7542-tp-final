/*
 * Consulta.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef CONSULTA_H_
#define CONSULTA_H_

#include "Definiciones.h"
#include "Mensaje.h"
class Consulta : public Mensaje {
public:
	Consulta();
	Consulta(const Consulta& original);
	virtual ~Consulta();

	/*
	 * Serializa toda la Consulta en string
	 */
	std::string serializar() const;

	/*
	 * Deserializa la Consulta a partir del string
	 */
	void deserializar(const std::string& consulta);

	// Deja la consulta vacia
	void limpiar();
	// Deja sin resultados la consulta pero conservando Filtros y Entradas
	void limpiarResultados();

	/*
	 * Agrega un Filtro a la Consulta
	 */
	void agregarFiltro(const std::string& filtro, const std::string& valor);
	/*
	 * Agrega una Entrada a la Consulta
	 */
	void agregarEntrada(const std::string entrada,
				const std::string valor);
	/*
	 * Agrega un Resultado a la Consulta
	 */
	void agregarResultado(const std::string& resultado);

	/*
	 * Define la funcion de agregacion que tendra la consulta.
	 * Por defecto es "NADA"
	 */
	void defininirAgregacion(Agregacion agregacion, const std::string& resultado);

	/*
	 * Define a la consulta como de "Cliente"
	 */
	void definirComoConsultaCliente();
	/*
	 * Define a la consulta como de "Agente"
	 */
	void definirComoConsultaAgente();

	// Define a la Consulta para que la respuesta sea una tabla pivote
	void definirConsultaDeTablaPivote();

	//void definirTablaPivote(const std::string& x, const std::string& y);

	void agregarXTablaP(const std::string& x);
	void agregarYTablaP(const std::string& y);

	const std::string& xDeTablaPivote(unsigned i) const;
	const std::string& yDeTablaPivote(unsigned i) const;

	unsigned cantVarXTabla() const;
	unsigned cantVarYTabla() const;

	bool esConsultaDeTablaPivote() const;

	// Agrega un campo a la consulta hecha por el Agente
	void agregarCampo(const std::string& campo);

	// Retorna la cantidad de filtros que tiene la consulta
	unsigned cantidadFiltros() const;
	/*
	 * Retorna la cantidad de Entradas que tiene la consulta
	 */
	unsigned cantidadEntradas() const;
	/*
	 * Retorna la cantidad de Resultados que posee la consulta
	 */
	unsigned cantidadResultados() const;

	unsigned cantidadCampos() const;

	/*
	 * Retorna el Filtro indexado por el argumento indice
	 */
	const std::string& filtro(unsigned indice) const;

	/*
	 * Retorna el valor del Filtro indexado por el argumento indice
	 */
	const std::string& valorFiltro(unsigned indice) const;

	/*
	 * Retorna el valor del Filtro indexado por el Filtro
	 */
	const std::string& valorFiltro(const std::string& filtro) const;

	/*
	 * Retorna la Entrada indexada por el argumento indice
	 */
	const std::string& entrada(unsigned indice) const;
	/*
	 * Retorna el Valor de la Entrada indexada por el argumento indice
	 */
	const std::string& valorEntrada(unsigned indice) const;

	const std::string& valorEntrada(const std::string& entrada) const;

	/*
	 * Retorna cual que es resultado indexado por el argumento indice
	 */
	const std::string& resultado(unsigned indice) const;


	/*
	 * Retorna la agregacion Agregacion de resultado.
	 */
	Agregacion agregacionDeResultado(unsigned indice) const;


	/*
	 * Retorna un campo de la "Consulta" hecha por el agente.
	 */
	const std::string& campo(unsigned indice) const;

	/*
	 * Retorna un bool indicando si es una consulta del Cliente
	 */
	bool esConsultaDeCliente() const;
	/*
	 * Retorna un bool indicando si es una consulta del Agente
	 */
	bool esConsultaDeAgente() const;

private:
	/*
	 * Guarda los "Filtros" de la consulta en el string datos a serializar
	 */
	void cargarFiltros(std::string& datos) const;
	/*
	 * Guarda los "Resultados" de la consulta en el string datos a serializar
	 */
	 void cargarResultados(std::string& datos) const;
	/*
	 * Guarda los "Entradas" de la consulta en el string datos a serializar
	 */
	void cargarEntradas(std::string& datos) const;

	void cargarVarDeTabla(std::string& datos) const;

	void guardarFiltros(const std::string& filtros);
	void guardarResultados(const std::string& resultados);
	void guardarEntradas(const std::string& entradas);
	void guardarVarDeTabla(const std::string& variables);

	Filtros _filtros;
	Entradas _entradas;
	Resultados _resultados;

	EntradasTabla _xTabla;
	EntradasTabla _yTabla;
	bool _consultaTablaPivote;

	Campos &_campos;

	Agregaciones _agregaciones;

	bool _consultaDeCliente;
	bool _consultaValida;

	static std::string s_nulo;
};

#endif /* CONSULTA_H_ */
