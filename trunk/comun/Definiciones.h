/*
 * Definiciones.h
 *
 *  Created on: 28/05/2012
 *      Author: migue
 */

#ifndef DEFINICIONES_H_
#define DEFINICIONES_H_

#include <vector>
#include <map>
#include <list>
#include <string>

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
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////

/*
 * Estructura para guardas las Entradas ("Inputs")  de una la Consulta
 */
typedef std::map<std::string, std::string> Entradas;

/*
 * Estructura para guardar los Filtros de una consulta
 */
typedef std::map<std::string, std::string> Filtros;

/*
 * Estructura para guardar los Resultados que utiliza la Consulta
 */
typedef std::vector<std::string> Resultados;


typedef Filtros Campos;


/////////////////////////////////////////////////////////////
//
// Estructuras para Respuesta
//
/////////////////////////////////////////////////////////////


typedef std::vector<std::string> Fila;

/*
 * Estructura para Guardar todos los datos que contiene una Respuesta
 */
typedef std::vector<Fila> DatosDeRespuesta;

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/*
 * Separador para determinar el fin de un Mensaje
 */
#define sep_fin '\03'

/*
 * Separador del tipo de Dato
 */
#define sep_tipo '\04'

/*
 * Separador de valores para un mismo tipo de dato
 */
#define sep_datos  '\05'

/*
 * Separador para utilizar en una entrada ( entrada , valor)
 */
#define sep_valor '\06'

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

/*
 * Identificador de que la consulta pertenece al Agente
 */

#define mensaje_agente 'A'

/*
 * Identificador de que la consulta pertenece al Agente
 */
#define mensaje_cliente 'C'

/////////////////////////////////////////////////////////
//
//TiposDatos para Socket
//
/////////////////////////////////////////////////////////

typedef unsigned short int Puerto;

#endif /* DEFINICIONES_H_ */
