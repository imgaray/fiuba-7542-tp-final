/*
 * Serializable.h
 *
 *  Created on: 05/07/2012
 *      Author: migue
 */

#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include "DefinicionesXML.h"

class Serializable {
public:
    virtual NodoXml serializar() = 0;
    virtual void deserializar(const NodoXml& nodo) = 0;
};

#endif /* SERIALIZABLE_H_ */
