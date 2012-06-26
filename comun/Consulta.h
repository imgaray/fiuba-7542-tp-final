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
#include "Utilitario.h"

/*
 * @DOC:
						Clase Consulta

	Esta clase es la encargada de guardar y administrar la consulta realizada
	por un Cliente o Agente, para que sea enviada al servidor y sea resuelta
	por este.

Atributos:

	Id_Mensaje _id: Id numerico para identificar univocamente a un Consulta
*
	Filtros _filtros: contenedor que almacena los filtros y sus valores para
	una consulta
*
	Entradas _entradas: contenedor que almacena las entradas y sus valores para
	una consulta.
*
	Resultados _resultados: contenedor que almacena los resultados que se quieren
	obtener de la consulta.
*
	EntradasTabla _xTabla: contenedor utilizado para guardar el grupo X de dimensiones
	y/o	hechos para una consulta de Tabla Pivote.
*
	EntradasTabla _yTabla: contenedor utilizado para guardar el grupo Y de dimensiones
	y/o	hechos para una consulta de Tabla Pivote.
*
	bool _consultaTablaPivote: booleano que indica si la consulta es de tabla pivote o
	es un a consulta normal.
*
	Campos &_campos: contenedor que guarda los campos para una consulta hecha por una
	agente.
*
	Agregaciones _agregaciones: contenedor que guarda las agregaciones que tiene que hacerse
	para en los resultados.
*
	bool _consultaDeCliente: booleano indicando si la consulta es de un cliente, en caso de que sea
	false la consulta seria de un agente.
*
	bool _consultaValida: booleano indicando si la consulta es valida o correcta en su contenido.
*
	static std::string s_nulo: string utilizado como referencia a string vacia.
 * @END
 * */


class Consulta : public Mensaje {
public:
	Consulta();
	Consulta(const Consulta& original);
	virtual ~Consulta();

	Consulta& operator=(const Consulta& original);

	void definirID(const Id_Mensaje& id);

	Id_Mensaje devolverID() const;

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

	// Retorna el campo "i" de la Tabla Pivote para el grupo X o Y
	const std::string& xDeTablaPivote(unsigned i) const;
	const std::string& yDeTablaPivote(unsigned i) const;

	// Retorna la cantidad de Campos que tiene el grupo X o Y de la Tabla Pivote
	unsigned cantVarXTabla() const;
	unsigned cantVarYTabla() const;

	// Retorna un bool indicando si la consulta es de una Tabla Pivote
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

	/*
	 *  Retorna la cantidad de campos que tiene la consulta
	 *  (Para que la utilice un a Agente)
	 */
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
	 *  o por la entrada misma
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

	void cargarID(std::string& datos) const;

	/*
	 * Metodos utilizados en la deserializacion de
	 * la Consulta
	 */
	void guardarFiltros(const std::string& filtros);
	void guardarResultados(const std::string& resultados);
	void guardarEntradas(const std::string& entradas);
	void guardarVarDeTabla(const std::string& variables);
	void guardarID(const std::string& id);

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

	//Utilitario u;

	Id_Mensaje _id;
};

#endif /* CONSULTA_H_ */
