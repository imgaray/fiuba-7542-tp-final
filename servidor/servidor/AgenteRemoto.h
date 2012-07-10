#ifndef __AGENTEREMOTO_H
#define __AGENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorEntradas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include "Mutex.h"
#include "Definiciones.h"

/** @class AgenteRemoto
	Esta clase es el proxy del agente. A través de la misma el servidor
obtendrá entradas de actualización y enviará respuestas. Es, a su vez,
un productor que alimenta la cola de consultas del servidor. Se maneja
en un hilo aparte, dado que existe un AgenteRemoto por agente
conectado al servidor.
*/

class AgenteRemoto: public Hilo {
private:
    Mutex m; /* Es un mutex que se utiliza para manejar correctamente el envío
	de respuestas a traves del socket al agente.*/
	
	Socket* agente; /* Es el socket que se encuentra conectado al agente. El
	AgenteRemoto se debe encargar de liberarlo y cerrarlo debidamente.*/
	
	ResolvedorEntradas& blresolvedor; /* La interfaz resolvedor entrada nos
	permite desacoplarnos de lo que sea que haya abajo. El unico requisito
	es que mantenga el invariante de que las entradas sólo se resuelven
	de a una. */
	
	unsigned id; /* Un id de cliente remoto, que sirve para identificación */
	
	ConsultasAgentesServidor& cconsultas; /* Es una referencia a la cola de
	consultas de los agentes del servidor. Es la cola que contiene todos
	los pedidos de actualización que tiene el servidor. La misma debe ser
	tread-safe. */
public:


	/**
		Método que se ejecuta mientras esté en ejecucion el hilo. Es el
		encargado de recibir elementos del socket y encolarlos para que
		responda el servidor.
	*/
	void correr();

	/**
		Detiene la ejecución del agente remoto, sin cerrar el hilo.
	*/
	void detener_agente();

	/** Desconecta el socket del agente remoto. */
	void desconectar_agente();

	/**
	Envía la respuesta obtenida del servidor al agente.
	*/	
	void enviarRespuesta(Respuesta& r);

	/**
		Constructor del agente remoto.
		@param agt El socket activo conectado con el servidor.
		@param rentr Objeto que sea capaz de resolver entradas.
		@param cons Cola de consultas de agentes del servidor.
	*/
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr, ConsultasAgentesServidor& cons);

	/**
		Destructor de agente remoto. Si esta corriendo, lo detiene. Si
		esta conectado, lo desconecta
	*/
	~AgenteRemoto();
};

#endif
