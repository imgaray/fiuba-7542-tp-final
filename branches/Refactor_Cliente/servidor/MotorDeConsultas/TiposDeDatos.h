/*
 * TiposDeDatos.h
 *
 *  Created on: 31/05/2012
 *      Author: migue
 */

#ifndef TIPOSDEDATOS_H_
#define TIPOSDEDATOS_H_
#include <map>
#include <list>
#include <set>
#include <string>
#include "../../comun/Definiciones.h"

#define sep_campos sep_datos

typedef std::string Dimension;
typedef unsigned int Hecho;

typedef size_t Id_Registro;

typedef std::multimap < FechaNumerica, Id_Registro > MapaDeFechas;

typedef std::list < Id_Registro > Lista_Id;

typedef std::set <Dimension> ConjuntoValoresDimension;

typedef std::string Combinacion;

typedef std::multimap < std::string, Id_Registro > MapaCombinaciones;

typedef std::pair <Combinacion, Id_Registro> parMapaCombinaciones;

typedef std::pair <MapaCombinaciones::const_iterator, MapaCombinaciones::const_iterator> parItMapaCombinaciones;

#endif /* TIPOSDEDATOS_H_ */
