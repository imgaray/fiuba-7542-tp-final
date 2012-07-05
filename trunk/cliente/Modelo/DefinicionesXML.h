/*
 * DefinicionesXML.h
 *
 *  Created on: 05/07/2012
 *      Author: migue
 */

#ifndef DEFINICIONESXML_H_
#define DEFINICIONESXML_H_
#include <exception>
#include "tinyxml.h"

typedef TiXmlElement NodoXml;

class ErrorSerializacionXML : public std::exception {
};

#endif /* DEFINICIONESXML_H_ */
