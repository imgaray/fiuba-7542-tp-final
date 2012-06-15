#ifndef __CLIENTEREMOTO_H
#define __CLIENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorConsultas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include <iostream>
using namespace std;

class ClienteRemoto: public Hilo {
private:
	Socket* cliente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorConsultas& blresolvedor;
public:

	// detiene la ejecucion del cliente. Cierra la conexion, detiene y
	// sincroniza el hilo
	void detener_cliente();
	
	// metodo que se corre mientras este en ejecucion el hilo. Resuelve
	// y envia consultas
	void correr();
	
	// constructor de clienteremoto. Recibe un socket conectado al cliente
	// y un resolvedor de consultas
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons);
	
	// destructor. Si esta corriendo, lo detiene. Si sigue conectado, 
	// desconecta
	~ClienteRemoto();
};

#endif
