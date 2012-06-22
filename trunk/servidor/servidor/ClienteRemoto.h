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

class ClienteRemoto: public Hilo {
private:
    Mutex m;
	Socket* cliente;
	// este resolvedor DEBE ser bloqueante
	ResolvedorConsultas& blresolvedor;
	ConsultasClientesServidor& cs;

public:

	void correr();

	// detiene la ejecucion del cliente. Cierra la conexion, detiene y
	// sincroniza el hilo
	void detener_cliente();

	void enviarRespuesta(Respuesta& r);

	// constructor de clienteremoto. Recibe un socket conectado al cliente
	// y un resolvedor de consultas
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons, ConsultasClientesServidor& cons);

	// destructor. Si esta corriendo, lo detiene. Si sigue conectado,
	// desconecta
	~ClienteRemoto();
};

#endif
