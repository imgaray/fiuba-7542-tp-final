#ifndef __THREADENTRADACLIENTES__H
#define __THREADENTRADACLIENTES__H

#include "../../comun/Socket.h"
#include "ContenedorClientes.h"
#include "ResolvedorConsultas.h"
#include "ClienteRemoto.h"
#include "../../comun/Hilo.h"
#include "../../comun/Definiciones.h"

class ThreadEntradaClientes: public Hilo {
private:
	Socket* entradaClientes;
	ContenedorClientes& cc;
	ResolvedorConsultas& rc;
	Puerto pclientes;
public:
	// metodo que se encarga de escuchar las conexiones de clientes entrantes
	// si encuentra un cliente, crea un ClienteRemoto y lo manda a correr
	void correr();
	
	// Desconecta, detiene y sincroniza el hilo
	void detener_entrada();
	
	// constructor. Debe recibir un contenedor de clientes que sera el que
	// vaya a poseer todos los clientes y un resolvedor de consultas, que 
	// se encargara de las consultas del cliente
	ThreadEntradaClientes(ContenedorClientes& ccli, ResolvedorConsultas& rcons, Puerto pclientes);
	
	// destructor. Si esta corriendo, para. Si esta conectado, desconecta
	~ThreadEntradaClientes();
};

#endif
