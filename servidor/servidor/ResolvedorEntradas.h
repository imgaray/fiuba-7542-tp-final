#ifndef _RESOLVEDORENTRADAS_H
#define _RESOLVEDORENTRADAS_H

/** @class ResolvedorEntradas
 * Interfaz que implementan los objetos que intervienen en la resolución
 * de entradas de agentes. */

class ResolvedorEntradas {
public:	
/** Método que deben redefinir. Deben devolver una respuesta válida. */
	virtual Respuesta resolverEntrada(Consulta& entrada) = 0;
	virtual ~ResolvedorEntradas() {}
};

#endif
