#ifndef _INTERMEDIARIO_SERVIDOR_H
#define _INTERMEDIARIO_SERVIDOR_H

class IntermediarioServidor {
private:
	ResolvedorConsulta* resolvedor;
public:

	// construye el intermediario con el puerto recibido por parametro
	IntermediarioServidor(ResolvedorConsulta* port);
	
	// destruye el intermediario, cerrando conexiones e hilos
	~IntermediarioServidor();
	
	// comienza la actividad del servidor
	void comenzar();
	
	// detiene la actividad del servidor
	void detener();
};

#endif
