/*
 * Agente.h
 *
 *  Created on: 26/05/2012
 *      Author: migue
 */

#ifndef AGENTE_H_
#define AGENTE_H_
#include "../comun/Socket.h"

class Agente {
public:
	Agente(const std::string& huespedServidor);
	void cargarDesdeConsola();
	void cargarDesdeArchivo();
	virtual ~Agente();
private:
	Socket _sck;
	std::string _huesped;
};

#endif /* AGENTE_H_ */
