#ifndef _HILORESPONDERCONSULTA_H
#define _HILORESPONDERCONSULTA_H

#include "Definiciones.h"
#include "ResolvedorConsultas.h"
#include "Hilo.h"
#include "ClienteRemoto.h"

class HiloResponderConsulta: public Hilo {
private:
	ConsultasClientesServidor& cconsultas;
	ResolvedorConsultas& resolvedor;
public:
	HiloResponderConsulta(ConsultasClientesServidor& cconsultas, ResolvedorConsultas& rcons);
	~HiloResponderConsulta();
	void correr();
};

#endif
