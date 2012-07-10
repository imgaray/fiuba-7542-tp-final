#ifndef __CLIENTEREMOTO_H
#define __CLIENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorConsultas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include "Mutex.h"
#include <iostream>
using namespace std;

/** @class ClienteRemoto
						 
	Esta clase es el proxy del cliente. A través de la misma el servidor
obtendrá consultas realizadas y enviará respuestas. Es tambien
un productor que alimenta la cola de consultas del servidor. Se maneja
en un hilo aparte, dado que existe un ClienteRemoto por cliente
conectado al servidor.
*/ 

class ClienteRemoto: public Hilo {
private:
    Mutex m; /* es un mutex que se utiliza para manejar correctamente el envio
	de respuestas a traves del socket al cliente. */
	
	Socket* cliente; /* es el socket que se encuentra conectado al agente. El
	ClienteRemoto se debe encargar de liberarlo y cerrarlo debidamente.*/
	
	// este resolvedor DEBE ser bloqueante
	
	ResolvedorConsultas& blresolvedor; /* la interfaz resolvedor consultas nos
	permite desacoplarnos de lo que sea que haya abajo. El unico requisito
	es que mantenta el invariante de que las consultas se deben ejecutar
	en paralelo. */
	
	ConsultasClientesServidor& cs; /* es una referencia a la cola de
	consultas de los clientes del servidor. Es la cola que contiene todos
	los pedidos de consulta que tiene el servidor. La misma debe ser
	tread-safe. */

public:
	/**	Método que se ejecuta mientras este en ejecución el hilo. Es el
		encargado de recibir elementos del socket y encolarlos para que
		responda el servidor. */
	void correr();

	/** Detiene la ejecución del cliente remoto.*/
	void detener_cliente();

	/** Desconecta el socket del cliente. */
	void desconectar_cliente();

	/** Envía la respuesta obtenida del servidor al cliente.	*/
	void enviarRespuesta(Respuesta& r);

	/** constructor del servidor remoto.
	 * @param cl Socket activo conectado.
	 * @param rcons Objeto encargado de resolver consultas.
	 * @param cons Cola de consultas de cliente del servidor.
	*/
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons, ConsultasClientesServidor& cons);

	/**
		Destructor de cliente remoto. Si esta corriendo, lo detiene. Si
		esta conectado, lo desconecta.
	*/
	~ClienteRemoto();
};

#endif
