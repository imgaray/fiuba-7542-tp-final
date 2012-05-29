/*
 * Respuesta.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef RESPUESTA_H_
#define RESPUESTA_H_

class Respuesta {
public:
	Respuesta();
	virtual ~Respuesta();

	/*
	 * Serializa la Respuesta en un string
	 */
	std::string serializar();
	/*
	 * Deserializa la Respuesta a partir de un string
	 */
	void deserializar(const std::string& datos);

	/*
	 * Define las columnas que tendra la respuesta.
	 */
	void definirColumnas(int columnas);

	/*
	 * Agrega un campo a la fila argumento
	 */
	void agregar(int fila, const std::string dato);

	/*
	 * Finaliza la fila actual y comienza una nueva
	 */
	void filaCompletada();

	/*
	 * Retorna el string encontrado en la fila  y columna argumentos
	 */
	const std::string& dato(int fila, int columna);

	/*
	 * Retorna la cantidad de Columnas que posee la respuesta
	 */
	int cantidadColumnas() const;
	/*
	 * Rertorna la cantidad de FIlas que posee la respuesta
	 */
	int cantidadFilas() const;

private:
	int _filas;
	DatosDeRespuesta _datos;
};

#endif /* RESPUESTA_H_ */
