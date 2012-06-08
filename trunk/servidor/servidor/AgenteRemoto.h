#ifndef __AGENTEREMOTO_H
#define __AGENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorEntradas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"

class AgenteRemoto: public Hilo {
private:
	Socket* agente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorEntradas& blresolvedor;
public:
	// Detiene la ejecucion del agente remoto. Cierra la conexion, detiene
	// y sincroniza
	void detener_agente();
	
	// metodo que se ejecuta mientras este corriendo el hilo
	void correr();
	
	// constructor del agente remoto. Recibe el socket activo conectado
	// con el servidor y un resolvedor de entradas
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr);
	
	// destructor de agente remoto. Si esta corriendo, lo detiene. Si
	// esta conectado, lo desconecta
	~AgenteRemoto();
};

#endif
