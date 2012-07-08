/*
 * Respuesta.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef RESPUESTA_H_
#define RESPUESTA_H_

#include "Definiciones.h"
#include "Mensaje.h"
#include "Utilitario.h"
#include <string>


/**
 * @class Respuesta
 *  Esta clase se encarga guardar lo relacionado a la
 * resolucion de una consulta ya sea desde un agente o un servidor.
 */

class Respuesta : public Mensaje {
public:
	Respuesta();
	Respuesta(const Respuesta& original);
	virtual ~Respuesta();

	/**
	 * @brief Constructor de respuesta que se instancia con un mensaje
	 * interno espefico.
	 * @param mensaje string que contiene el mensaje para la respuesta intanciada.
	 */
	Respuesta(const std::string& mensaje);

	/**
	 * @brief Define cual es el identificador que tendra la respuesta(Por defecto es 0).
	 * @param id es nuevo indetificado de la Respuesta.
	 */
	void definirID(const Id_Mensaje& id);

	/**
	 * @brief Retorna el identificador actual del mensaje.
	 * @return Id de la Respuesta.
	 */
	Id_Mensaje devolverID() const;

	/**
	 * @brief Serializa la Respuesta en un string.
	 * @return string que contiene la Respuesta Serializada.
	 */
	std::string serializar() const;

	/**
	 * @brief Deserializa la Respuesta a partir de un string.
	 * @param datos string que contiene los datos de la Respuesta serializada.
	 */
	void deserializar(const std::string& datos);

	/**
	 * @brief Metodo que implementa el operador= para hacer una copia de Respuesta.
	 * @param resp Respuesta a la cual se le realizara la copia.
	 * @return referencia de la Respuesta actual
	 */
	Respuesta& operator=(const Respuesta& resp);

	/**
	 * @brief Retorna un mensaje Interno que posee una instancia de respuesta.
	 * @return string del mensaje que contiene respuesta.
	 */
	const std::string& mensajeInterno() const;

	/**
	 * @brief Se define cual es el mensaje interno de la respuesta.
	 * @param mensaje string que contiene el nuevo mensaje interno.
	 */
	void mensajeInterno(const std::string& mensaje);

	/**
	 * @brief Deja la Respuesta vacia.
	 */
	void limpiar();

	/**
	 * @brief Define las columnas que tendra la respuesta.
	 * @param columnas la nueva cantidad de columnas.
	 */
	void definirColumnas(size_t columnas);

	/**
	 * @brief Agrega un campo Nuevo en la fila actual donde es que se encuentra.
	 * @param dato string con el nuevo campo.
	 */
	void agregar(const std::string& dato);

	/**
	 * @brief Establece el fin de la fila actual y comienza una nueva.
	 */
	void filaCompletada();

	/**
	 * @brief Retorna el campo encontrado en la fila  y columna argumentos. Si se
	 * sobrepasan los argumentos se retorna un string nulo.
	 * @param fila es la fila del dato
	 * @param columna es la columna del dato
	 * @return string que contiene el campo recuperado.
	 */
	const std::string& dato(size_t fila, size_t columna) const;

	/**
	 * @brief Retorna la cantidad de Columnas que posee la respuesta
	 * @return cantidad de columnas actual.
	 */
	size_t cantidadColumnas() const;

	/**
	 * @brief Rertorna la cantidad de FIlas que posee la respuesta.
	 * @return cantidad de filas actual.
	 */
	size_t cantidadFilas() const;

	/**
	 * @brief Retorna un bool indicando si en la respuesta recibida
	 * se encuentra algun mensaje de Error.
	 * @return booleano indicandi si hubo error.
	 */
	bool huboError() const;


	static std::string mensajeError;
	static std::string respuestaVacia;
	static std::string respuestaValida;

private:
	/**
	 * @brief Metodo utilizado para deserializar una Respuesta.
	 * Guardando los datos del argumentos fila en la estructura
	 * interna de la clase Respuesta.
	 * @param fila string que contiene una fila completa serializada.
	 */
	void guardarFila(const std::string& fila);

	/**
	 * @brief Metodo utilizado para serializar una Respuesta.
	 * Guardando los datos del argumento Fila en el string datos.
	 * @param fila Fila a la cual se va serializar.
	 * @param datos string donde se guardara la Fila serializada.
	 */
	void cargarFila(const Fila& fila, std::string& datos) const;

	size_t _columnas;
	DatosDeRespuesta _datos;
	Fila _filaActual;

	std::string _msjInterno;

	static Campo campo_nulo;

    Utilitario u;

    Id_Mensaje _id;
};

#endif /* RESPUESTA_H_ */
