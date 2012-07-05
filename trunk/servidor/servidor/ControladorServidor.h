#ifndef __CONTROLADOR_H
#define __CONTROLADOR_H

//#include "BLQueue.h"
//#include "BLMap.h"
#include <utility>
#include <list>
#include "ClienteRemoto.h"
#include "AgenteRemoto.h"
#include "ContenedorAgentes.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ResolvedorEntradas.h"
#include "Consulta.h"
#include "ThreadEntradaAgentes.h"
#include "ThreadEntradaClientes.h"
#include "Mutex.h"
#include <iostream>
#include "Definiciones.h"
#include "PoolClientes.h"
#include "PoolAgentes.h"
using namespace std;

/* @DOC
	Clase ControladorServidor

	Esta clase es fundamental. Su rol es controlar el flujo correcto de
resolucion de consultas y actualizaciones. Se encarga de permitir que
el servidor maneje multiples consultas, como tambien de frenarlas cuando
se requiera de procesar actualizaciones. Contiene un Pool de workers, cada
uno con una dedicacion a alguna de las tareas ya sean de actualizacion
como de consultas. Implementa interfaces como ResolvedorConsultas, ResolvedorEntradas,
ContenedorClientes y ContenedorAgentes, que hace que sus workers solo vean
lo que necesiten ver de el.

	Es el encargado tambien de leer la configuracion de puetos que va a tener
el servidor, de manejar los hilos que se encargan de recibir clientes y
agentes. En definitiva, es el encargado de la coordinacion de la concurrencia
del servidor.

Atributos:

	ConsultasAgentesServidor centradas: es la cola que contendra todos los
	pedidos de actualizacion recibidos de los agentes. Dicha cola es thread
	safe y sera compartida con todos los workers que esten en el pool de
	workers para agentes.
	
	ConsultasClientesServidor cconsultas: es la cola que contendra todos los
	pedidos de consultas recibidos de los clientes. Dicha cola es thread safe
	y sera compartida con todos los workers que esten en el pool de workers
	para clientes.

	unsigned int ncons: es un indicador de la cantidad de consultas en
	proceso, que es distinto a la cantidad de consultas encoladas. Sirve
	para poder coordinar las consultas y las actualizaciones.
	
	unsigned int nact: es un indicador de la cantidad de entradas en proceso,
	que es distinto a la cantidad de entradas encoladas. Sirve para coordinar
	el proceso de actualizacion con el de consulta. A diferencia de ncons,
	nact debe ser o 1 o 0.

	lclientes clientes: es la lista que contiene todos los proxy de los clientes
	conectados. Se utiliza para poder detenerlos y eliminarlos en caso de que se
	quiera cerrar el servidor.

	Puerto puerto_clientes: es el numero de puerto por el cual se conectan
	los clientes.

	Puerto puerto_agentes: es el numero de puerto por el cual se conectan
	los agentes.
	
	lagentes agentes: es la lista que contiene todos los proxy de los agentes
	conectados. Se utiliza para poder detenerlos y eliminarlos en caso de que
	se quiera cerrar el servidor.

	ResolvedorConsultas& rcons: contiene una referencia al objeto que se
	encargue de resolver las consultas.

	ResolvedorEntradas& rentr: contiene una referencia al objeto que se
	encargue de resolver las entradas.

	ThreadEntradaAgentes* tagentes: este hilo se encargara de recibir todas
	las conexiones ingresantes de los agentes.

	ThreadEntradaClientes* tclientes: este hilo se encargara de recibir todas
	las conexiones ingresantes de los clientes.
	
	PoolClientes poolclientes: este es el pool de workers que minara de
	la cola de consultas de clientes.
	
	PoolAgentes poolagentes: este es el pool de workers que minara de la
	cola de consultas de agentes.
	
	Mutex m: este mutex es el que se utilizara para coordinar las actualizaciones
	y las consultas.
	
* @END*/

class ControladorServidor:  public ResolvedorConsultas, 
							public ResolvedorEntradas,
							public ContenedorClientes,
							public ContenedorAgentes {
private:
	// atributos
	ConsultasAgentesServidor centradas;
	ConsultasClientesServidor cconsultas;
	typedef std::list<ClienteRemoto*> lclientes;
	typedef std::list<AgenteRemoto*> lagentes;
	unsigned int ncons;
	unsigned int nact;
	bool corriendo;
	lclientes clientes;
	Puerto puerto_clientes;
	Puerto puerto_agentes;
	lagentes agentes;
	ResolvedorConsultas& rcons;
	ResolvedorEntradas& rentr;
	ThreadEntradaAgentes* tagentes;
	ThreadEntradaClientes* tclientes;
	PoolClientes poolclientes;
	PoolAgentes poolagentes;
	Mutex m;
public:
/* @DOC
Metodos publicos
@END
*/

	/* 
	@DOC
	Respuesta resolverEntrada(Consulta& entrada)
		Este metodo es el encargado de resolver las actualizaciones. Si
		hay consultas resolviendose en el momento de la llamada, este metodo
		quedara bloqueado hasta que pueda realizar la actualizacion.
	@END*/
	Respuesta resolverEntrada(Consulta& entrada);
	
		/* 
	@DOC
	Respuesta resolver(Consulta& entrada)
		Este metodo es el encargado de resolver las consultas. Si
		hay entradas resolviendose en el momento de la llamada, este metodo
		quedara bloqueado hasta que pueda realizar la consulta. Sin embargo
		este metodo no se bloqueara si ortas consultas estan en proceso,
		permitiendo la resolucion de consultas de forma concurrente.
	@END*/
	Respuesta resolver(Consulta& consulta);
	
	/*
	 @DOC
	 ControladorServidor(ResolvedorConsultas& cons, ResolvedorEntradas& rent,
								Puerto pclientes, Puerto pagentes)
		Este es el constructor de controladorServidor. Debe recibir a los
		resolvedores correspondientes y los puertos que seran utilizados
		por los agentes.
	 
	 @END*/
	ControladorServidor(ResolvedorConsultas& cons, ResolvedorEntradas& rent,
								Puerto pclientes, Puerto pagentes);
	
	/* @DOC
		bool activo();
			Metodo utilizado para saber si las entradas siguen activas.
	@END*/
	
	bool activo();
	
	/*
	 *@DOC
	~ControladorServidor()
		El destructor del controlador. Si esta en ejecucion, libera toda
		la memoria que corresponda, cerrando conexiones y deteniendo hilos.
	@END*/
	~ControladorServidor();
	
	/* @DOC
	void agregarCliente(ClienteRemoto* rem)
		El metodo que permite agregar un cliente remoto a su lista. Es el
		heredado de la interfaz ContenedorClientes.
	@END
	*/
	void agregarCliente(ClienteRemoto* rem);
	
	/* @DOC
	void agregarAgente(AgenteRemoto* rem)
		El metodo que permite agregar un agente remoto a su lista. Es el
		heredado de la interfaz ContenedorAgentes.
	@END
	*/
	void agregarAgente(AgenteRemoto* agt);
	
	/* @DOC
	void comenzar()
		Se encarga de inicar los hilos correspondientes a los que escuchan
		conexiones y a los pools de workers.
	@END */
	void comenzar();
	
	/* @DOC
	void detener()
		Se encarga de detener todos los hilos, tanto los workers como los
		que escuchan conexiones ingresantes, cierra las colas de consultas y
		realiza tareas varias previas a la destruccion del mismo.
		@END
	*/
	void detener();
};

#endif
