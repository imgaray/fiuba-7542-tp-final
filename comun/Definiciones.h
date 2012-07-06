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
#include "BLMap.h"
#include "BLQueue.h"
#include <utility>
class Consulta;
class Respuesta;
class Consultante;
class AgenteRemoto;
class ClienteRemoto;

/*
 * Identificador para los mensajes tanto Consulta como Respuesta
 */

typedef size_t Id_Mensaje;

/*
 * Tipo de Funcion de agregacion para una consulta
 */

#define PRIMER_VALOR 65

enum Agregacion {
	NADA = PRIMER_VALOR,	// Ninguno
	SUM,	                // Suma
	MAX,	                // Maximo
	MIN,	                // Minimo
	PROM,	                // Promedio
	CONT	                // Contar
};
///////////////////////////////////////////////////////
// Estructuras Para Consulta
///////////////////////////////////////////////////////

typedef std::string Campo;

typedef std::string Fecha;

typedef size_t FechaNumerica;

/*
 * Estructura para guardas las Entradas ("Inputs")  de una la Consulta
 */
typedef std::map < std::string, std::string > Entradas;

/*
 * Estructura para guardar los Filtros de una consulta
 */
typedef std::map < std::string, std::string > Filtros;

/*
 * Contenedor para guardar campos de un registro
 */

typedef std::list < Campo > Campos;
/*
 * Estructura para guardar los Resultados que utiliza la Consulta
 */

typedef Campos Resultados;

/*
 * Estructura para guardar las Agregaciones
 */
typedef std::vector <Agregacion> Agregaciones;

/*
 * Estructura para guardar las tablas
 */

typedef std::vector <Campo> EntradasTabla;
/////////////////////////////////////////////////////////////
//
// Estructuras para Respuesta
//
/////////////////////////////////////////////////////////////


typedef std::vector < std::string > Fila;

/*
 * Estructura para Guardar todos los datos que contiene una Respuesta
 */
typedef std::vector < Fila > DatosDeRespuesta;

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


// Separador para determinar el fin de un Mensaje
#define sep_fin '\03'

// Separador del tipo de Dato
#define sep_tipo  '%'// '\04'

// Separador de valores para un mismo tipo de dato
#define sep_datos '\05'

// Separador para utilizar en una entrada ( entrada , valor)
#define sep_valor '|'//\06'

#define sep_fecha '\07'
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

#define STR_NULA ""

/////////////////////////////////////////////////////////
//
//Constantes (provisorias) de conexion, como puertos y demas
//
/////////////////////////////////////////////////////////

#define PORT_CLIENTE (Puerto) 4321
#define PORT_AGENTE (Puerto) 12345

/////////////////////////////////////////////////////////
//
// Tipos de datos para el servidor
//
/////////////////////////////////////////////////////////

typedef std::pair<AgenteRemoto*, Consulta> ConsultaAgenteServidor;
typedef std::pair<ClienteRemoto*, Consulta> ConsultaClienteServidor;
typedef BLQueue<ConsultaAgenteServidor> ConsultasAgentesServidor;
typedef BLQueue<ConsultaClienteServidor> ConsultasClientesServidor;

/////////////////////////////////////////////////////////
//
//TiposDatos para ServidorRemoto (cliente)
//
/////////////////////////////////////////////////////////

typedef std::pair<unsigned, Consulta> ParConsulta;
typedef std::pair<unsigned, Respuesta> ParRespuesta;
typedef BLQueue<ParConsulta> ColaConsultas;
typedef BLQueue<ParRespuesta> ColaRespuestas;
typedef BLMap<unsigned, Consultante*> MapaConsultantes;
typedef BLMap<unsigned, bool> BitmapCancelados;

/////////////////////////////////////////////////////////
//
//TiposDatos para Socket
//
/////////////////////////////////////////////////////////

typedef unsigned short int Puerto;

#define PUERTO_ESTANDAR_AGENTE (Puerto)4321

/////////////////////////////////////////////////////////
//
//Definiciones de atributos de Archivo Configuracion cliente
//
/////////////////////////////////////////////////////////

#define CLAVE_ATR "claveAdmin"

#endif /* DEFINICIONES_H_ */
