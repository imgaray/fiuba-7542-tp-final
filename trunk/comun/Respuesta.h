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

class Respuesta : public Mensaje {
public:
	Respuesta();
	Respuesta(const Respuesta& original);
	virtual ~Respuesta();

	/*
	 *  Constructor de respuesta que se instancia con un mensaje
	 *  interno espefico
	 */
	Respuesta(const std::string& mensaje);

	void definirID(const Id_Mensaje& id);

	Id_Mensaje devolverID() const;

	// Serializa la Respuesta en un string
	std::string serializar() const;

	// Deserializa la Respuesta a partir de un string
	void deserializar(const std::string& datos);

	// Metodo que implementa el operador= para hacer una copia de Respuesta
	Respuesta& operator=(const Respuesta& resp);

	// Retorna un mensaje Interno que posee una instancia de respuesta
	const std::string& mensajeInterno() const;

	// Se define cual es el mensaje interno de la respuesta
	void mensajeInterno(const std::string& mensaje);

	/*
	 * Deja la Respuesta vacia
	 */
	void limpiar();

	/*
	 * Define las columnas que tendra la respuesta.
	 */
	void definirColumnas(size_t columnas);

	/*
	 * Agrega un campo a la fila argumento
	 */
	void agregar(const std::string& dato);

	/*
	 * Finaliza la fila actual y comienza una nueva
	 */
	void filaCompletada();

	/*
	 * Retorna el string encontrado en la fila  y columna argumentos
	 */
	const std::string& dato(size_t fila, size_t columna) const;

	/*
	 * Retorna la cantidad de Columnas que posee la respuesta
	 */
	size_t cantidadColumnas() const;
	/*
	 * Rertorna la cantidad de FIlas que posee la respuesta
	 */
	size_t cantidadFilas() const;

	/*
	 * Retorna un bool indicando si en la respuesta recibida
	 * se encuentra algun mensaje de Error
	 */
	bool huboError() const;


	static std::string mensajeError;
	static std::string respuestaVacia;
	static std::string respuestaValida;

private:
	/*
	 * Metodo utilizado para deserializar una Respuesta.
	 * Guardando los datos del argumentos fila en la estructura
	 * interna de la clase Respuesta
	 */
	void guardarFila(const std::string& fila);

	/*
	 * Metodo utilizado para serializar una Respuesta.
	 * Guardando los datos del argumento Fila en el string datos.
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
