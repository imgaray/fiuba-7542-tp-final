#ifndef _THREADCLIENTE_H
#define _THREADCLIENTE_H

#include "../comun/Hilo.h"
#include "ResolvedorConsulta.h"

class ThreadCliente: public Hilo {
private:
	Socket* cliente;
	ResolvedorConsulta* resolvedor;
public:
	bool mandarRespuesta(Respuesta& respuesta);
	bool obtenerConsulta(Consulta& consulta);
	ThreadCliente(Socket* cliente);
	~ThreadCliente();
	void correr();
};

#endif
