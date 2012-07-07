#ifndef __THREADENTRADACLIENTES__H
#define __THREADENTRADACLIENTES__H

#include "../../comun/Socket.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ClienteRemoto.h"
#include "../../comun/Hilo.h"
#include "../../comun/Definiciones.h"

/** @class ThreadEntradaClientes
 
	Esta clase es la encargada de recepcionar las conexiones ingresantes de
clientes. Al ingresar una conexión, crea un ClienteRemoto, lo guarda y lo pone
a correr. */

class ThreadEntradaClientes: public Hilo {
private:
	Socket* entradaClientes;
	ContenedorClientes& cc;
	ResolvedorConsultas& rc;
	Puerto pclientes;
	ConsultasClientesServidor& cconsultas;
public:

	bool activo();

	/** Método que se encarga de escuchar las conexiones de clientes entrantes
	 si encuentra un cliente, crea un ClienteRemoto y lo manda a correr. */
	void correr();
	
	/** Desconecta, detiene y sincroniza el hilo. */
	void detener_entrada();
	
	/** La ùnica acción realizada durante la creación del objeto es la de
	 * enlazar el socket.
	 * @param ccli Objeto capaz de almacenar los ClientesRemotos.
	 * @param rcons Objeto capaz de resolver las consultas.
	 * @param pclientes Puerto por el cual escuchará conexiones de los clientes.
	 * @param ccons Cola de consultas del servidor. */
	ThreadEntradaClientes(ContenedorClientes& ccli, ResolvedorConsultas& rcons,
					Puerto pclientes, ConsultasClientesServidor& ccons);
	
	/** Si esta corriendo, se detiene. Si esta conectado, desconecta. */
	~ThreadEntradaClientes();
};

#endif
