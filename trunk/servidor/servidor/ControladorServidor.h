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

/** @class ControladorServidor

	Esta clase es fundamental. Su rol es controlar el flujo correcto de
resolución de consultas y actualizaciones. Se encarga de permitir que
el servidor maneje múltiples consultas, como también de frenarlas cuando
se requiera de procesar actualizaciones. Contiene un Pool de "workers", cada
uno con una dedicación a alguna de las tareas ya sean de actualización
como de consultas. Implementa interfaces como ResolvedorConsultas, ResolvedorEntradas,
ContenedorClientes y ContenedorAgentes, que hace que sus "workers" sólo vean
lo que necesiten ver del controlador.

	Es la clase encargada también de manejar los hilos que se encargan de recibir clientes y
agentes. En definitiva, es el encargado de la coordinacion de la concurrencia
del servidor.
*/

class ControladorServidor:  public ResolvedorConsultas, 
							public ResolvedorEntradas,
							public ContenedorClientes,
							public ContenedorAgentes {
private:
	// atributos
	
	ConsultasAgentesServidor centradas; /* es la cola que contendrá todos los
	pedidos de actualización recibidos de los agentes. Dicha cola es thread
	safe y será compartida con todos los workers que esten en el pool de
	workers para agentes. */
	
	ConsultasClientesServidor cconsultas; /* es la cola que contendrá todos los
	pedidos de consultas recibidos de los clientes. Dicha cola es thread safe
	y sera compartida con todos los workers que esten en el pool de workers
	para clientes. */
	
	typedef std::list<ClienteRemoto*> lclientes; 
	
	typedef std::list<AgenteRemoto*> lagentes; 
	
	unsigned int ncons; /* es un indicador de 
	la cantidad de consultas en proceso, que es distinto a la cantidad
	de consultas encoladas. Sirve para poder coordinar las consultas y 
	las actualizaciones. */
	
	unsigned int nact; /* es un indicador de la cantidad de entradas en proceso,
	que es distinto a la cantidad de entradas encoladas. Sirve para coordinar
	el proceso de actualizacion con el de consulta. A diferencia de ncons,
	nact debe ser o 1 o 0. */
	
	bool corriendo;
	
	lclientes clientes;/* lista que contendrá
	todos los clientes conectados al servidor. */
	
	Puerto puerto_clientes; /* es el numero de puerto por el cual se conectan
	los clientes. */
	
	Puerto puerto_agentes; /* es el numero de puerto por el cual se conectan
	los agentes. */
	
	lagentes agentes; /* lista que contendrá todos
	los agentes conectados al servidor. */
	
	ResolvedorConsultas& rcons; /* contiene una referencia al objeto que se
	encargue de resolver las consultas. */
	
	ResolvedorEntradas& rentr; /* contiene una referencia al objeto que se
	encargue de resolver las entradas. */
	
	ThreadEntradaAgentes* tagentes; /* este hilo se encargara de recibir todas
	las conexiones ingresantes de los agentes. */
	
	ThreadEntradaClientes* tclientes; /* este hilo se encargara de recibir todas
	las conexiones ingresantes de los clientes. */
	
	PoolClientes poolclientes; /* este es el pool de workers que minara de
	la cola de consultas de clientes. */
	
	PoolAgentes poolagentes; /* este es el pool de workers que minara de la
	cola de consultas de agentes. */

	Mutex m; /* este mutex es el que se utilizara para coordinar las actualizaciones
	y las consultas. */
	
public:

	/**	Este método es el encargado de resolver las actualizaciones. Si
		hay consultas resolviéndose en el momento de la llamada, quedará
		bloqueado hasta que pueda realizar la actualización. */
	Respuesta resolverEntrada(Consulta& entrada);
	
		/** Este método es el encargado de resolver las consultas. Si
		hay entradas resolviéndose en el momento de la llamada, este método
		quedará bloqueado hasta que pueda realizar la consulta. Sin embargo
		no se bloqueara si otras consultas están en proceso, permitiendo
		la resolución de consultas de forma concurrente. */
	Respuesta resolver(Consulta& consulta);
	
	/** Constructor de controladorServidor.
	 * @param cons Objeto que resuelva las consultas.
	 * @param rent Objeto que resuelva las entradas.
	 * @param pclientes Puerto por el cual se escucharán conexiones entrantes
	 * de los clientes.
	 * @param pagentes Puerto por el cual se escucharán conexiones entrantes
	 * de los agentes. */
	ControladorServidor(ResolvedorConsultas& cons, ResolvedorEntradas& rent,
								Puerto pclientes, Puerto pagentes);
	
	/**	Método utilizado para saber si las entradas siguen activas. */
	bool activo();
	
	/**	El destructor del controlador. Si esta en ejecución, libera toda
		la memoria que corresponda, cerrando conexiones y deteniendo hilos. */
	~ControladorServidor();
	
	/** El método que permite agregar un cliente remoto a su lista. Es el
		heredado de la interfaz ContenedorClientes. */
	void agregarCliente(ClienteRemoto* rem);
	
	/**	El método que permite agregar un agente remoto a su lista. Es el
		heredado de la interfaz ContenedorAgentes. */
	void agregarAgente(AgenteRemoto* agt);
	
	/**	Se encarga de inicar los hilos correspondientes a los que escuchan
		conexiones y a los pools de workers. */
	void comenzar();
	
	/**	Se encarga de detener todos los hilos, tanto los workers como los
		que escuchan conexiones ingresantes, cierra las colas de consultas y
		realiza tareas varias previas a la destruccion del mismo. */
	void detener();
};

#endif
