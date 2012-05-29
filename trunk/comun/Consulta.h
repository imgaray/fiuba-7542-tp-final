/*
 * Consulta.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef CONSULTA_H_
#define CONSULTA_H_

#include "Definiciones.h"

class Consulta {
public:
	Consulta();
	virtual ~Consulta();

	/*
	 * Serializa toda la Consulta en string
	 */
	std::string serializar();

	/*
	 * Deserializa la Consulta a partir del string
	 */
	void deserializar(const std::string& consulta);

	/*
	 * Agrega un Filtro a la Consulta
	 */
	void agregarFiltro(const std::string filtro);
	/*
	 * Agrega una Entrada a la Consulta
	 */
	void agregarEntrada(const std::string entrada,
				const std::string valor);
	/*
	 * Agrega un Resultado a la Consulta
	 */
	void agregarResultado(const std::string resultado);



	/*
	 * Define a la consulta como de "Cliente"
	 */
	void definirComoConsultaCliente();
	/*
	 * Define a la consulta como de "Agente"
	 */
	void definirComoConsultaAgente();


	/*
	 * Agrega un campo a la consulta hecha por el Agente
	 */
	void agregarCampo(const std::string campo);

	/*
	 * Retorna la cantidad de filtros que tiene la consulta
	 */
	int cantidadFiltros() const;
	/*
	 * Retorna la cantidad de Entradas que tiene la consulta
	 */
	int cantidadEntradas() const;
	/*
	 * Retorna la cantidad de Resultados que posee la consulta
	 */
	int cantidadResultados() const;

	/*
	 * Retorna el Filtro indexado por el argumento indice
	 */
	const std::string& filtro(int indice) const;
	/*
	 * Retorna la Entrada indexada por el argumento indice
	 */
	const std::string& entrada(int indice) const;
	/*
	 * Retorna el Valor de la Entrada indexada por el argumento indice
	 */
	const std::string& valorEntrada(int indice) const;
	/*
	 * Retorna cual que es resultado indexado por el argumento indice
	 */
	const std::string& resultado(int indice) const;

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
	 * Guarda los "Filtros" de la consulta en el string datos
	 */
	void guardarFiltros(std::string& datos);
	/*
	 * Guarda los "Resultados" de la consulta en el string datos
	 */
	void guardarResultados(std::string& datos);
	/*
	 * Guarda los "Entradas" de la consulta en el string datos
	 */
	void guardarEntradas(std::string&datos);

	Filtros _filtros;
	Entradas _entradas;
	Resultados _resultados;

	Campos &_campos;

	bool _consultaDeCliente;
	bool _consultaValida;
};

#endif /* CONSULTA_H_ */
