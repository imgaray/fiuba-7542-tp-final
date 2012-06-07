#ifndef _RESOLVEDORENTRADAS_H
#define _RESOLVEDORENTRADAS_H

class ResolvedorEntradas {
public:	
	virtual Respuesta resolverEntrada(Consulta& entrada) = 0;
	virtual ~ResolvedorEntradas() {}
};

#endif
