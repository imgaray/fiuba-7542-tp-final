#ifndef _RESOLVEDORCONSULTAS_H
#define _RESOLVEDORCONSULTAS_H
#include "Consulta.h"
#include "Respuesta.h"

class ResolvedorConsultas {
public:
	virtual Respuesta resolver(Consulta& consulta) = 0;
	virtual ~ResolvedorConsultas() {}
};

#endif
