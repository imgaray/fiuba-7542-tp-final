#ifndef _RESOLVEDORCONSULTAS_H
#define _RESOLVEDORCONSULTAS_H
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"

class ResolvedorConsultas {
public:
	virtual Respuesta resolver(Consulta& consulta) = 0;
	virtual ~ResolvedorConsultas() {}
};

#endif
