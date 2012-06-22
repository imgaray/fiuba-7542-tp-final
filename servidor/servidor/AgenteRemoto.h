#ifndef __AGENTEREMOTO_H
#define __AGENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorEntradas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include "Mutex.h"
#include "Definiciones.h"

class AgenteRemoto: public Hilo {
private:
    Mutex m;
	Socket* agente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorEntradas& blresolvedor;
	unsigned id;
	ConsultasAgentesServidor& cconsultas;

public:

	void correr();

	// Detiene la ejecucion del agente remoto. Cierra la conexion, detiene
	// y sincroniza
	void detener_agente();

	void enviarRespuesta(Respuesta& r);

	// constructor del agente remoto. Recibe el socket activo conectado
	// con el servidor y un resolvedor de entradas
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr, ConsultasAgentesServidor& cons);

	// destructor de agente remoto. Si esta corriendo, lo detiene. Si
	// esta conectado, lo desconecta
	~AgenteRemoto();
};

#endif
