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
#include <string>

class Respuesta : public Mensaje {
public:
	Respuesta();
	Respuesta(const Respuesta& original);
	Respuesta(const std::string& mensaje);

	virtual ~Respuesta();

	// Serializa la Respuesta en un string
	std::string serializar() const;

	// Deserializa la Respuesta a partir de un string
	void deserializar(const std::string& datos);

	void operator=(const Respuesta& resp);

	const std::string& mensajeInterno() const;

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

private:
	void guardarFila(const std::string& fila);

	void cargarFila(const Fila& fila, std::string& datos) const;

	size_t _columnas;
	DatosDeRespuesta _datos;
	Fila _filaActual;

	std::string _msjInterno;

	static Campo campo_nulo;
};

#endif /* RESPUESTA_H_ */
