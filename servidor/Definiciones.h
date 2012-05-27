/*
 * Definiciones.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

/*
 * Tipo de Funcion de agregacion para una consulta
 */
enum Agregacion {
	NADA,	// Ninguno
	SUM,	// Suma
	MAX,	// Maximo
	MIN,	// Minimo
	PROM,	// Promedio
	CONT	// Contar
};


/*
 * Identificador para los registro del archivo de datos
 */
typedef unsigned int Id_Registro;

#endif /* DEFINICIONES_H_ */
