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

/**
 *  @class 	Esta clase es la encargada de guardar y administrar la consulta realizada
 *	por un Cliente o Agente, para que sea enviada al servidor y sea resuelta
 *	por este.
 */

class Consulta : public Mensaje {
public:
	/**
	 * @brief Constructor sin argumentos.
	 */
	Consulta();
	Consulta(const Consulta& original);
	virtual ~Consulta();

	/**
	 * @brief Realiza la copia de otro Consulta.
	 * @param original consulta a copiar.
	 * @return referecia de la Consulta actual.
	 */
	Consulta& operator=(const Consulta& original);

	/**
	 * @brief Define un nuevo identificador para la Consulta(por defecto es 0).
	 * @param id nuevo identificador.
	 */
	void definirID(const Id_Mensaje& id);

	/**
	 * @brief Devuelve el identificador de la Consulta.
	 * @return id de la Consulta.
	 */
	Id_Mensaje devolverID() const;

	/**
	 * @brief Serializa toda la Consulta en string
	 * @return string que contiene la Consulta serializada.
	 */
	std::string serializar() const;

	/**
	 * @brief Deserializa la Consulta a partir del string
	 * @para consulta string con que contiene la consulta serializada
	 */
	void deserializar(const std::string& consulta);


	/**
	 * @brief Deja la consulta vacia.
	 */
	void limpiar();

	/**
	 * @brief Deja la Consulta sin Resultados pero conservando Filtros y Entradas.
	 */
	void limpiarResultados();

	/**
	 * @brief Agrega un Filtro a la Consulta
	 * @param filtro string con el nombre del filtro
	 * @param valor string que contiene el valor del filtro
	 */
	void agregarFiltro(const std::string& filtro, const std::string& valor);

	/**
	 * @brief Agrega una Entrada a la Consulta.
	 * @param entrada string con el nombre de la entrada
	 * @param valor strinq que contiene el valor de la entrada.
	 */
	void agregarEntrada(const std::string entrada,
				const std::string valor);

	/**
	 * @brief Agrega un Resultado a la Consulta, la agregacion por defecto
	 * para el resultado agregado es "NADA".
	 * @param resultado string que contiene el nombre del campo a agregar.
	 */
	void agregarResultado(const std::string& resultado);

	/**
	 * @brief Agrega un Resultado a la consulta y define la agregacion del mismo.
	 * @param agregacion tipo de agregacion para el resultado
	 * @param resultado string que contiene el nombre del campo resultado.
	 */
	void defininirAgregacion(Agregacion agregacion, const std::string& resultado);

	/**
	 * @brief Define el estado de la Consulta como consulta de "Cliente"
	 */
	void definirComoConsultaCliente();

	/**
	 * @brief Define el estado de la Consulta como consulta como de "Agente"
	 */
	void definirComoConsultaAgente();

	/**
	 * @brief Define a la Consulta para que la respuesta sea una tabla pivote
	 */
	void definirConsultaDeTablaPivote();

	/**
	 * @brief agrega un campo al Grupo X de la Tabla Pivote
	 * @param x string con el nombre del campo a agregar.
	 */
	void agregarXTablaP(const std::string& x);

	/**
	 * @brief agrega un campo al Grupo Y de la Tabla Pivote
	 * @param y string con el nombre del campo a agregar.
	 */
	void agregarYTablaP(const std::string& y);

	/**
	 * @brief  Retorna el campo "i" de la Tabla Pivote para el grupo X
	 * @param i indice del campo en el Grupo.
	 * @return nombre del campo.
	 */
	const std::string& xDeTablaPivote(unsigned i) const;

	/**
	 * @brief  Retorna el campo "i" de la Tabla Pivote para el grupo Y
	 * @param i indice del campo en el Grupo.
	 * @return nombre del campo.
	 */
	const std::string& yDeTablaPivote(unsigned i) const;

	/**
	 * @brief Indica la cantidad de campos que hay en el Grupo X de la Tabla Pivote.
	 * @return cantidad de Campos
	 */
	unsigned cantVarXTabla() const;

	/**
	 * @brief Indica la cantidad de campos que hay en el Grupo Y de la Tabla Pivote.
	 * @return cantidad de Campos.
	 */
	unsigned cantVarYTabla() const;

	/**
	 * @brief Indica si la consulta es de una Tabla Pivote
	 * @return booleano que indica si consulta de Tabla Pivote
	 */
	bool esConsultaDeTablaPivote() const;

	/**
	 * @brief  Agrega un campo a la consulta hecha por el Agente.
	 * @param campo string que contiene el valor de un campo.
	 */
	void agregarCampo(const std::string& campo);

	/**
	 * @brief  Retorna la cantidad de filtros que tiene la consulta
	 * @return cantidad de Filtros.
	 */
	unsigned cantidadFiltros() const;

	/**
	 * @brief Retorna la cantidad de Entradas que tiene la consulta
	 * @return cantidad de Entradas.
	 */
	unsigned cantidadEntradas() const;

	/**
	 * @brief Retorna la cantidad de Resultados que posee la consulta.
	 * @return cantidad de Resultados.
	 */
	unsigned cantidadResultados() const;

	/**
	 * @brief Retorna la cantidad de campos que tiene la consulta
	 * (Para que la utilice un a Agente).
	 * @return cantidad de campos.
	 */
	unsigned cantidadCampos() const;

	/**
	 * @brief Retorna el Filtro indexado por el argumento indice.
	 * @param indice es el indice del Filtro dentro de la Consulta
	 * @return nombre del Filtro recuperado.
	 */
	const std::string& filtro(unsigned indice) const;

	/**
	 * @brief Retorna el valor del Filtro indexado por el argumento indice.
	 * @param indice es el indice del Filtro dentro de la Consulta
	 * @return string que contiene el valor del Filtro indexado.
	 */
	const std::string& valorFiltro(unsigned indice) const;

	/**
	 * @brief Retorna el valor del Filtro indexado por el mismo filtro.
	 * @param filtro es el nombre del filtro dentro de la consulta.
	 * @return string que contiene el valor del Filtro indexado.
	 */
	const std::string& valorFiltro(const std::string& filtro) const;

	/**
	 * @brief Retorna la Entrada indexada por el argumento indice.
	 * @param indice es el indice de la Entrada dentro de la Consulta.
	 * @return string que contiene el nombre de la Entrada.
	 */
	const std::string& entrada(unsigned indice) const;

	/**
	 * @brief Retorna el Valor de la Entrada indexada por el argumento indice
	 * o por la entrada misma.
	 * @param indice es el indice de la Entrada dentro de la Consulta
	 * @return string que contiene el valor de la Entrada.
	 */
	const std::string& valorEntrada(unsigned indice) const;

	/**
	 * @brief Retorna el Valor de la Entrada indexada por la misma entrada.
	 * @param entrada string con el nombre de la Entrada.
	 * @return string que contiene el valor de la Entrada.
	 */
	const std::string& valorEntrada(const std::string& entrada) const;

	/**
	 * @brief Retorna el nombre de un resultado indexado por el argumento indice.
	 * @param indice es el numero del Resultado dentro de la consulta.
	 * @return string que contiene el nombre del Resultado recuperado.
	 */
	const std::string& resultado(unsigned indice) const;

	/**
	 * @brief Retorna la agregacion Agregacion de Resultado.
	 * @param indice es el numero del Resultado dentro de la consulta.
	 * @return agregacion del resultado.
	 */
	Agregacion agregacionDeResultado(unsigned indice) const;


	/**
	 * @brief Retorna un campo de la "Consulta" hecha por el agente, indexado por indice.
	 * @param indice es el numero del campo dentro de la Consulta.
	 * @return string que contiene el nombre del Campo Recuperado.
	 */
	const std::string& campo(unsigned indice) const;

	/**
	 * @brief Indica si la Consulta si es una consulta de Cliente.
	 * @return booleano que indica si una consulta de Cliente.
	 */
	bool esConsultaDeCliente() const;

	/**
	 * @brief Indica si es una consulta de Agente.
	 * @return booleano que indica si una consulta de Agente.
	 */
	bool esConsultaDeAgente() const;

private:
	/**
	 * Guarda los "Filtros" de la consulta en el string datos a serializar
	 */
	void cargarFiltros(std::string& datos) const;
	/**
	 * Guarda los "Resultados" de la consulta en el string datos a serializar
	 */
	 void cargarResultados(std::string& datos) const;
	
	/**
	 * Guarda los "Entradas" de la consulta en el string datos a serializar
	 */
	void cargarEntradas(std::string& datos) const;

	void cargarVarDeTabla(std::string& datos) const;

	void cargarID(std::string& datos) const;

	/**
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

	Id_Mensaje _id;
};

#endif /* CONSULTA_H_ */
