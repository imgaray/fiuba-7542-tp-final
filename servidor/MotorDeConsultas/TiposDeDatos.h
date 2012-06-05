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


typedef std::string Dimension;
typedef unsigned int Hecho;

typedef size_t Id_Registro;

typedef std::multimap < FechaNumerica, Id_Registro > MapaDeFechas;

typedef std::list < Id_Registro > Lista_Id;

typedef std::set <Dimension> ConjuntoValoresDimension;

#endif /* TIPOSDEDATOS_H_ */
