/*ervidor::
 * VerificadorEntradasH.h
 *
 *  Created on: 09/06/2012
 *      Author: migue
 */

#ifndef __VERIFICADORENTRADAS_H
#define __VERIFICADORENTRADAS_H
class Consulta;

class VerificadorEntradasH {
public:
	VerificadorEntradasH() {}
	~VerificadorEntradasH() {}
	bool verificarEntrada(const Consulta& entrada);
};

#endif
