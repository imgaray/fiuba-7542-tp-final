#ifndef _HILORESPONDERENTRADA_H
#define _HILORESPONDERENTRADA_H

#include "Definiciones.h"
#include "ResolvedorEntradas.h"
#include "Hilo.h"
#include "AgenteRemoto.h"

class HiloResponderEntrada: public Hilo {
private:
	ConsultasAgentesServidor& centradas;
	ResolvedorEntradas& resolvedor;
public:
	HiloResponderEntrada(ConsultasAgentesServidor& cconsultas, ResolvedorEntradas& rentr);
	~HiloResponderEntrada();
	void correr();
};

#endif
