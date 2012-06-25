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

/*
 * @DOC:
						Clase ClienteRemoto
						 
	Esta clase es el proxy del cliente. A traves de la misma el servidor
obtendra consultas realizadas y enviara respuestas. Es, a su vez,
producer que alimenta la cola de consultas del servidor. Se maneja
en un hilo aparte, dado que va a haber un ClienteRemoto por cliente
conectado al servidor.
 
Atributos:

	Mutex m: es un mutex que se utiliza para manejar correctamente el envio
	de respuestas a traves del socket al cliente.
 * 
	Socket* cliente: es el socket que se encuentra conectado al agente. El
	ClienteRemoto se debe encargar de liberarlo y cerrarlo debidamente.
 * 
	ResolvedorConsultas& blresolvedor: la interfaz resolvedor consultas nos
	permite desacoplarnos de lo que sea que haya abajo. El unico requisito
	es que mantenta el invariante de que las consultas se deben ejecutar
	en paralelo.
 * 
	unsigned id: un id de cliente remoto, que sirve para identificacion
 * 
	ConsultasClientesServidor& cconsultas: es una referencia a la cola de
	consultas de los clientes del servidor. Es la cola que contiene todos
	los pedidos de consulta que tiene el servidor. La misma debe ser
	tread safe.
 * @END
 * */

class ClienteRemoto: public Hilo {
private:
    Mutex m;
	Socket* cliente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorConsultas& blresolvedor;
	ConsultasClientesServidor& cs;

public:
/* @DOC
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
	 void detener_cliente()
		Detiene la ejecucion del cliente remoto. Cierra la conexion, detiene
		y sincroniza
	 @END
	*/
	void detener_cliente();

	/* @DOC
	void enviarRespuesta(Respuesta& r)
		Envia la respuesta obtenida del servidor al cliente
	@END
	*/
	void enviarRespuesta(Respuesta& r);

	/* @DOC
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons, ConsultasClientesServidor& cons)
		constructor del servidor remoto. Recibe el socket activo conectado
		con el cliente, un resolvedor de consultas y la cola.
	@END
	*/
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons, ConsultasClientesServidor& cons);

	/* @DOC
	~ClienteRemoto()
		destructor de cliente remoto. Si esta corriendo, lo detiene. Si
		esta conectado, lo desconecta
	@END
	*/
	~ClienteRemoto();
};

#endif
