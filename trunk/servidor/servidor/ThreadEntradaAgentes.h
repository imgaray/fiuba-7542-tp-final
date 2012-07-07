#ifndef __THREADENTRADAAGENTES_H
#define __THREADENTRADAAGENTES_H

#include "../../comun/Socket.h"
#include "ContenedorAgentes.h"
#include "ResolvedorEntradas.h"
#include "AgenteRemoto.h"
#include "../../comun/Hilo.h"
#include "../../comun/Definiciones.h"

/** @class ThreadEntradaAgentes
 
	Esta clase es la encargada de recepcionar las conexiones ingresantes de
agentes. Al ingresar una conexión, crea un AgenteRemoto, lo guarda y lo pone
a correr. */

class ThreadEntradaAgentes: public Hilo {
private:
	Socket* entradaAgentes;
	ContenedorAgentes& ca;	
	ResolvedorEntradas& re;
	Puerto pagentes;
	ConsultasAgentesServidor& centradas;
public:

	bool activo();

	/** Método que se queda pendiente de la conexión de nuevos agentes. 
	Si llega un agente, crea un AgenteRemoto que procese las consultas. */
	void correr();
	
	/** Detiene la conexión de entrada de agentes. Desconecta, detiene y
	 sincroniza el hilo. */
	void detener_entrada();
	
	/** Al conectar la unica acción realizada es la de enlazamiento del socket.
	 * @param cag Objeto capaz de contener AgentesRemotos.
	 * @param rent Objeto capaz de resolver entradas. Será usado por los AgentesRemotos
	 * conectados.
	 * @param pagentes Puerto por el cual escuchará conexiones.
	 * @param centr Cola de consultas de agente del servidor. */
	ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent,
					Puerto pagentes, ConsultasAgentesServidor& centr);
	
	/** Detiene la entrada. Si sigue conectado, desconecta. */
	~ThreadEntradaAgentes();
};

#endif
