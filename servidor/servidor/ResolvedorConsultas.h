#ifndef _RESOLVEDORCONSULTAS_H
#define _RESOLVEDORCONSULTAS_H
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"

/** @class ResolvedorConsultas

	Es una interfaz que sirve para enmascarar las clases que intervienen
en la resolucion de consultas. */

class ResolvedorConsultas {
public:

	/** Método que deben implementar los Resolvedores. */
	virtual Respuesta resolver(Consulta& consulta) = 0;
	virtual ~ResolvedorConsultas() {}
};

#endif
