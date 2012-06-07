#ifndef __CONTENEDORCLIENTES_H
#define __CONTENEDORCLIENTES_H

#include "ClienteRemoto.h"

class ContenedorClientes {
public:
	virtual void agregarCliente(ClienteRemoto* agt) = 0;
	virtual ~ContenedorClientes() {}
};

#endif
