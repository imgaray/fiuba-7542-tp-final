#ifndef __CONTENEDORAGENTES_H
#define __CONTENEDORAGENTES_H

#include "AgenteRemoto.h"

class ContenedorAgentes {
public:
	virtual void agregarAgente(AgenteRemoto* agt) = 0;
	virtual ~ContenedorAgentes() {}
};

#endif
