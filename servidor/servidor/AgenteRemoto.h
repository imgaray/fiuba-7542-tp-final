#ifndef __AGENTEREMOTO_H
#define __AGENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorEntradas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include "Mutex.h"
#include "Definiciones.h"

/*
 * @DOC
							Clase AgenteRemoto
	Esta clase es el proxy del agente. A traves de la misma el servidor
obtendra entradas de actualizacion y enviara respuestas. Es, a su vez,
producer que alimenta la cola de consultas del servidor. Se maneja
en un hilo aparte, dado que va a haber un AgenteRemoto por agente
conectado al servidor.
 * 
Atributos:
 * 
	Mutex m: es un mutex que se utiliza para manejar correctamente el envio
	de respuestas a traves del socket al agente
 * 
	Socket* agente: es el socket que se encuentra conectado al agente. El
	AgenteRemoto se debe encargar de liberarlo y cerrarlo debidamente.
 * 
	ResolvedorEntradas& blresolvedor: la interfaz resolvedor entrada nos
	permite desacoplarnos de lo que sea que haya abajo. El unico requisito
	es que mantenta el invariante de que las entradas solo se resuelven
	de a una
 * 
	unsigned id: un id de cliente remoto, que sirve para identificacion
 * 
	ConsultasAgentesServidor& cconsultas: es una referencia a la cola de
	consultas de los agentes del servidor. Es la cola que contiene todos
	los pedidos de actualizacion que tiene el servidor. La misma debe ser
	tread safe.
 * @END
 * */

class AgenteRemoto: public Hilo {
private:
    Mutex m;
	Socket* agente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorEntradas& blresolvedor;
	unsigned id;
	ConsultasAgentesServidor& cconsultas;
public:
/*@DOC
Metodos publicos
@END */


	/* @DOC
	 void correr()
		Metodo que se ejecuta mientras este en ejecucion el hilo. Es el
		encargado de recibir elementos del socket y encolarlos para que
		responda el servidor
	 @END
	*/
	void correr();

	/* @DOC
	 void detener_agente()
		Detiene la ejecucion del agente remoto. Cierra la conexion, detiene
		y sincroniza
	 @END
	*/
	void detener_agente();

	/* @DOC
	void enviarRespuesta(Respuesta& r)
		Envia la respuesta obtenida del servidor al agente
	@END
	*/
	
	void desconectar_agente();
	
	void enviarRespuesta(Respuesta& r);

	/* @DOC
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr, ConsultasAgentesServidor& cons)
		constructor del agente remoto. Recibe el socket activo conectado
		con el servidor y un resolvedor de entradas
	@END
	*/
	AgenteRemoto(Socket* agt, ResolvedorEntradas& rentr, ConsultasAgentesServidor& cons);

	/* @DOC
	~AgenteRemoto()
		destructor de agente remoto. Si esta corriendo, lo detiene. Si
		esta conectado, lo desconecta
	@END
	*/
	~AgenteRemoto();
};

#endif
