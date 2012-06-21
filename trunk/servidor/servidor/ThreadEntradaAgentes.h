#ifndef __THREADENTRADAAGENTES_H
#define __THREADENTRADAAGENTES_H

#include "../../comun/Socket.h"
#include "ContenedorAgentes.h"
#include "ResolvedorEntradas.h"
#include "AgenteRemoto.h"
#include "../../comun/Hilo.h"
#include "../../comun/Definiciones.h"

class ThreadEntradaAgentes: public Hilo {
private:
	Socket* entradaAgentes;
	ContenedorAgentes& ca;	
	ResolvedorEntradas& re;
	Puerto pagentes;
	ConsultasAgentesServidor& centradas;
public:

	// metodo que se queda pendiente de la conexion de nuevos agentes. 
	// Si llega un agente, crea un AgenteRemoto que procesa las consultas
	void correr();
	
	// Detiene la conexion de entrada de agentes. Desconecta, detiene y
	// sincroniza el hilo
	void detener_entrada();
	
	// constructor. Recibe un ContenedorAgentes valido y un ResolvedorEntradas.
	// El primero sera el que contenga todos los AgenteRemoto. El segundo
	// el que resuelva las entradas que reciba de cada AgenteRemoto
	ThreadEntradaAgentes(ContenedorAgentes& cag, ResolvedorEntradas& rent,
					Puerto pagentes, ConsultasAgentesServidor& centr);
	
	// destructor. Detiene la entrada. Si sigue conectado, desconecta.
	~ThreadEntradaAgentes();
};

#endif
