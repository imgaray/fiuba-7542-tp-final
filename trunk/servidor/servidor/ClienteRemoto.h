#ifndef __CLIENTEREMOTO_H
#define __CLIENTEREMOTO_H

#include "../../comun/Hilo.h"
#include "../../comun/Socket.h"
#include "ResolvedorConsultas.h"
#include "../../comun/Consulta.h"
#include "../../comun/Respuesta.h"
#include <iostream>
#include "HiloConsumerEnviar.h"
#include "HiloConsumerRecibir.h"
#include "HiloConsumerResponderConsulta.h"
using namespace std;

class ClienteRemoto {
private:
	Socket* cliente;
	ConsultasServidor cconsultas;
	RespuestasServidor crespuestas;
	// este resolvedor DEBE ser bloqueante
	ResolvedorConsultas& blresolvedor;
	RespuestasServidor rs;
	ConsultasServidor cs;
	HiloConsumerEnviar hce;
	HiloConsumerRecibir hcr;
	HiloConsumerResponderConsulta hcrc;
	
public:

	void iniciar();
	
	// detiene la ejecucion del cliente. Cierra la conexion, detiene y
	// sincroniza el hilo
	void detener_cliente();
	
	// constructor de clienteremoto. Recibe un socket conectado al cliente
	// y un resolvedor de consultas
	ClienteRemoto(Socket* cl, ResolvedorConsultas& rcons);
	
	// destructor. Si esta corriendo, lo detiene. Si sigue conectado, 
	// desconecta
	~ClienteRemoto();
};

#endif
